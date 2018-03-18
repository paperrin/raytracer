#include "shared.h"
#include "obj_surface_normal.cl"
#include "shade.cl"
#include "atomic_add.cl"

t_ray				get_refracted_ray(t_ray ray, t_real3 hit_pos,
		t_real3 normal, t_real ior);

kernel void			kernel_ray_shade(
		constant read_only t_obj *objs,
		global read_only uint *objs_size,
		constant read_only t_material *mats,
		global read_only uint *mats_size,
		constant read_only t_light *lights,
		global read_only uint *lights_size,
		constant read_only t_texture *textures,
		global read_only uint *textures_size,
		global read_only cl_uchar *texture_pixels,
		global read_only ulong *n_texture_pixels,
		global read_write t_ray_state *ray_states,
		global read_write cl_float *pixels,
		global read_only t_config *config,
		global read_only uint *n_rays)
{
	const int				gid = get_global_id(0);
	t_real3					hit_pos;
	t_real3					normal;
	cl_float3				color;
	t_obj					obj;
	t_ray_state				state;
	t_ray_state				state_reflec;
	t_ray_state				state_refrac;
	char					has_reflection;
	char					has_refraction;

	state = ray_states[gid];
	color = (cl_float3)(0, 0, 0);
	has_reflection = 0;
	has_refraction = 0;
	state_refrac.importance = -1;
	state_reflec.importance = -1;
	state_refrac.obj_id = -1;
	state_reflec.obj_id = -1;
	if (state.obj_id > -1)
	{
		obj = objs[state.obj_id];
		hit_pos = state.ray.origin + state.t * state.ray.dir;
		normal = obj_surface_normal(&obj, hit_pos, state.ray);
		hit_pos += normal * (t_real)1e-3;
		color = shade(obj, hit_pos, state.ray,
				objs, *objs_size,
				mats, *mats_size,
				textures, *textures_size,
				texture_pixels, *n_texture_pixels,
				lights, *lights_size, config);
		color *= (state.importance - mats[obj.material_id].reflection - mats[obj.material_id].refraction);
		color /= config->samples_width * config->samples_width;
		atomic_addf(&pixels[state.pxl_id * 4 + 0], color.r);
		atomic_addf(&pixels[state.pxl_id * 4 + 1], color.g);
		atomic_addf(&pixels[state.pxl_id * 4 + 2], color.b);

		if (config->cur_depth < config->max_depth)
		{
				has_reflection = mats[obj.material_id].reflection > 1.f / 255;
				has_refraction = mats[obj.material_id].refraction > 1.f / 255;

				if (has_refraction)
				{
					state_refrac = state;
					state_refrac.ray = get_refracted_ray(state.ray, hit_pos, normal,
								mats[obj.material_id].indice_of_refraction);
					state_refrac.importance = state.importance * mats[obj.material_id].refraction;
					state_refrac.t = -1;
					state_refrac.obj_id = -1;
				}

				if (has_reflection)
				{
					state_reflec = state;
					state_reflec.ray = get_reflected_ray(state.ray, hit_pos, normal);
					state_reflec.importance = state.importance * mats[obj.material_id].reflection;
					state_reflec.t = -1;
					state_reflec.obj_id = -1;
				}
		}
	}
	if (config->cur_depth < config->max_depth)
	{
		ray_states[gid + *n_rays] = state_reflec;
		ray_states[gid] = state_refrac;
	}
}

t_ray				get_refracted_ray(t_ray ray, t_real3 hit_pos, t_real3 normal, t_real ior)
{
	t_ray			refr;

	refr.origin = hit_pos - normal * 1e-1f;
	if (dot(normal, ray.dir) < 0)
		refr.dir = -normal + (normal + ray.dir) * ior;
	else
		refr.dir = normal + (normal - ray.dir) * ior;
	return (refr);
}
