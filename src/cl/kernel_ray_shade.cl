#include "shared.h"
#include "obj_ray_hit.cl"
#include "obj_surface_normal.cl"
#include "light_get_dir.cl"

t_real				real_min_max(t_real min, t_real value, t_real max);
cl_float3			shade(t_obj obj, t_real3 hit_pos,
		constant t_obj *objs, cl_uint objs_size,
		constant t_material *mats, cl_uint mats_size,
		constant t_light *lights, cl_uint lights_size);
cl_float3			tone_map(cl_float3 color);
t_ray				get_reflected_ray(t_ray_state state, t_real3 hit_pos,
		t_real3 normal);

kernel void			kernel_ray_shade(
		constant read_only t_obj *objs,
		constant read_only uint *objs_size,
		constant read_only t_material *mats,
		constant read_only uint *mats_size,
		constant read_only t_light *lights,
		constant read_only uint *lights_size,
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
				lights, *lights_size)
			* (state.importance - mats[obj.material_id].reflection);
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

cl_float3			tone_map(cl_float3 color)
{
	color.r = color.r / (color.r + 1);
	color.g = color.g / (color.g + 1);
	color.b = color.b / (color.b + 1);
	return (color);
}

t_real				real_min_max(t_real min, t_real value, t_real max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

cl_float3			shade(t_obj obj, t_real3 hit_pos,
		constant t_obj *objs, cl_uint objs_size,
		constant t_material *mats, cl_uint mats_size,
		constant t_light *lights, cl_uint lights_size)
{
	t_real3			surface_normal;
	t_ray			light_ray;
	cl_float3		light_color;
	t_real			t;
	char			in_shadow;
	cl_float3		color;
	int				i;
	t_real			ndl;
	t_real			light_dist;

	surface_normal = obj_surface_normal(&obj, hit_pos);
	light_ray.origin = hit_pos;
	color = mats[obj.material_id].color * (cl_float3)(0.05, 0.05, 0.05);
	i = -1;
	while (++i < (int)lights_size)
	{
		light_ray.dir = light_get_dir(lights[i], hit_pos, &light_color, &light_dist);
		ndl = dot(light_ray.dir, surface_normal);
		if (ndl < 0)
			continue ;
		if (!(ray_throw_get_any_hit_obj(&light_ray, objs, objs_size, &t) > -1) || (light_dist <= t))
			color += mats[obj.material_id].color * light_color * (cl_float)ndl;
	}
	color = tone_map(color);
	return (color);
}
