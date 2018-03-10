#include "shared.h"
#include "obj_surface_normal.cl"
#include "shade.cl"
#include "atomic_add.cl"

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
		global read_write uint *n_new_rays,
		global read_write cl_float *pixels,
		global read_only t_config *config)
{
	const int				gid = get_global_id(0);
	t_real3					hit_pos;
	t_real3					normal;
	cl_float3				color;
	t_obj					obj;
	t_ray_state				state;
	char					has_reflection;

	state = ray_states[gid];
	color = (cl_float3)(0, 0, 0);
	has_reflection = 0;
	if (state.obj_id > -1)
	{
		obj = objs[state.obj_id];
		hit_pos = state.ray.origin + state.t * state.ray.dir;
		normal = obj_surface_normal(&obj, hit_pos);
		hit_pos += normal * (t_real)1e-10;
		color = shade(obj, state.ray, hit_pos,
				objs, *objs_size,
				mats, *mats_size,
				textures, *textures_size,
				texture_pixels, *n_texture_pixels,
				lights, *lights_size, config);
		color *= (state.importance - mats[obj.material_id].reflection);
		color /= config->samples_width * config->samples_width;
		atomic_addf(&pixels[state.pxl_id * 4 + 0], color.r);
		atomic_addf(&pixels[state.pxl_id * 4 + 1], color.g);
		atomic_addf(&pixels[state.pxl_id * 4 + 2], color.b);
		has_reflection = mats[obj.material_id].reflection > 1.f / 255;
		if (has_reflection)
		{
			atomic_inc(n_new_rays);
			state.ray = get_reflected_ray(state.ray, hit_pos, normal);
			state.importance *= mats[obj.material_id].reflection;
			state.t = -1;
			state.obj_id = -1;
		}
		else
			state.importance = -1;
	}
	else
		state.importance = -1;
	ray_states[gid] = state;
}
