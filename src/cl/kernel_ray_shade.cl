#include "host.h"
#include "obj_surface_normal.cl"
#include "shade.cl"
#include "atomic_add.cl"
#include "get_secondary_ray.cl"
#include "get_light_glare_color.cl"
#include "utils.cl"

kernel void			kernel_ray_shade(
		constant read_only t_obj *objs,
		global read_only uint *objs_size,
		constant read_only t_material *mats,
		read_only uint mats_size,
		constant read_only t_light *lights,
		read_only uint lights_size,
		constant read_only t_texture *textures,
		read_only uint textures_size,
		global read_only uchar *texture_pixels,
		read_only ulong n_texture_pixels,
		global read_write t_ray_state *ray_states,
		global read_write uint *n_new_rays,
		global read_write float *pixels,
		global read_only t_config *config,
		constant read_only t_camera_data *cam)
{
	const int				gid = get_global_id(0);
	t_real3					hit_pos;
	t_real3					normal;
	cl_float3				color;
	t_obj					obj;
	t_ray_state				state;
	t_ray_state				state_reflec;
	t_ray_state				state_refrac;
	float3					surface_color;
	char					has_reflection;
	char					has_refraction;
	int						block_size;
	int						middle_pos;
	int						n_screen_pixels;
	float					surface_refraction;

	state = ray_states[gid];
	color = (cl_float3)(0, 0, 0);
	has_reflection = 0;
	has_refraction = 0;
	state_refrac.importance = -1;
	state_reflec.importance = -1;
	if (state.obj_id > -1)
	{
		obj = objs[state.obj_id];
		hit_pos = state.ray.origin + state.t * state.ray.dir;
		normal = obj_surface_normal(&obj, hit_pos, state.ray);
		surface_color = obj_surface_color(&obj, mats, textures, textures_size,
				texture_pixels, n_texture_pixels, hit_pos);
		surface_refraction = obj_surface_refraction(&obj, mats, textures, textures_size,
				texture_pixels, n_texture_pixels, hit_pos);
		color = shade(config, obj, hit_pos, normal, surface_color, surface_refraction, state.ray,
				objs, *objs_size,
				mats, mats_size,
				textures, textures_size,
				texture_pixels, n_texture_pixels,
				lights, lights_size);

		color *= state.color_factor;
		color *= (state.importance - state.importance * (mats[obj.material_id].reflection + surface_refraction));

		if (config->cur_depth < config->max_depth)
		{
				has_reflection = mats[obj.material_id].reflection > config->color_epsilon;
				has_refraction = surface_refraction > config->color_epsilon;

				if (has_refraction)
				{
					state_refrac = state;
					atomic_inc(n_new_rays);
					state_refrac.ray = get_refracted_ray(config, &obj, state.ray, hit_pos, normal,
								mats[obj.material_id].refraction_index);
					state_refrac.importance = state.importance * surface_refraction;
					state_refrac.t = -1;
					state_refrac.obj_id = -1;
				}

				if (has_reflection)
				{
					state_reflec = state;
					atomic_inc(n_new_rays);
					state_reflec.ray = get_reflected_ray(config, state.ray, hit_pos, normal);
					state_reflec.importance = state.importance * mats[obj.material_id].reflection;
					state_reflec.t = -1;
					state_reflec.obj_id = -1;
				}
		}
	}

	if (config->cur_depth == 0)
		color += get_light_glare_color(config, objs, *objs_size, lights, lights_size, mats, mats_size, state.ray);

	color /= config->samples_width * config->samples_width;
	if (cam->is_anaglyph)
		color = filter_anaglyph(config, state.pxl_id, color);
	n_screen_pixels = get_screen_pixels_count(config);
	atomic_addf(&pixels[state.pxl_id % n_screen_pixels * 4 + 0], color.r);
	atomic_addf(&pixels[state.pxl_id % n_screen_pixels * 4 + 1], color.g);
	atomic_addf(&pixels[state.pxl_id % n_screen_pixels * 4 + 2], color.b);
	if (state.obj_id > -1)
		state.color_factor *= surface_color;

	if (config->cur_depth < config->max_depth)
	{
		block_size = config->screen_size.x * config->screen_size.y * (cam->is_anaglyph + 1);
		middle_pos = config->samples_width * config->samples_width * pown(2.f, config->cur_depth) * block_size;
		ray_states[gid % middle_pos] = state_refrac;
		ray_states[gid % middle_pos + middle_pos] = state_reflec;
	}
}
