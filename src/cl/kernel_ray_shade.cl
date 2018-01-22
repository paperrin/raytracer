#include "shared.h"
#include "obj_surface_normal.cl"
#include "shade.cl"

t_ray				get_reflected_ray(t_ray_state state, t_real3 hit_pos,
		t_real3 normal);

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
		global write_only cl_float *pixels,
		global read_only t_config *config)
{
	const int				gid = get_global_id(0);
	t_real3					hit_pos;
	t_real3					normal;
	cl_float3				color;
	t_obj					obj;
	t_ray_state				state;
	uint					new_id;
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
		color = shade(obj, hit_pos,
				objs, *objs_size,
				mats, *mats_size,
				textures, *textures_size,
				texture_pixels, *n_texture_pixels,
				lights, *lights_size);
		color *= (state.importance - mats[obj.material_id].reflection);
		has_reflection = mats[obj.material_id].reflection > 1e-4;
		if (has_reflection)
		{
			state.ray = get_reflected_ray(state, hit_pos, normal);
			state.importance *= mats[obj.material_id].reflection;
			state.t = -1;
			state.obj_id = -1;
		}
	}
	pixels[state.pxl_id * 4 + 0] += color.r;
	pixels[state.pxl_id * 4 + 1] += color.g;
	pixels[state.pxl_id * 4 + 2] += color.b;
	pixels[state.pxl_id * 4 + 3] = 1;
	barrier(CLK_GLOBAL_MEM_FENCE);
	if (has_reflection)
		new_id = atomic_inc(n_new_rays);
	if (config->ray_compaction && has_reflection)
		ray_states[new_id] = state;
	else	
		ray_states[gid] = state;
}

t_ray				get_reflected_ray(t_ray_state state, t_real3 hit_pos, t_real3 normal)
{
	t_ray		ray;

	ray.origin = hit_pos;
	ray.dir = state.ray.dir - (t_real)2 * dot(normal, state.ray.dir) * normal;
	return (ray);
}
