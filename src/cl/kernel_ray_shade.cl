#include "shared.h"
#include "obj_surface_normal.cl"
#include "shade.cl"

t_ray				get_reflected_ray(t_ray_state state, t_real3 hit_pos,
		t_real3 normal);
t_ray				get_refracted_ray(t_ray_state state, t_real3 hit_pos,
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
				lights, *lights_size, config->ambient);
		color *= (state.importance - mats[obj.material_id].reflection - mats[obj.material_id].refraction);
		pixels[state.pxl_id * 4 + 0] += color.r;		
		pixels[state.pxl_id * 4 + 1] += color.g;
		pixels[state.pxl_id * 4 + 2] += color.b;

		if (config->cur_depth < config->max_depth)
		{
				has_reflection = mats[obj.material_id].reflection > 1e-4;
				has_refraction = mats[obj.material_id].refraction > 1e-4;

				if (has_refraction)
				{
					state_refrac = state;
					atomic_inc(n_new_rays);
					state_refrac.ray = get_refracted_ray(state, hit_pos, normal, mats[obj.material_id].indice_of_refraction);
					state_refrac.importance = state.importance * mats[obj.material_id].refraction;
					state_refrac.t = -1;
					state_refrac.obj_id = -1;
				}

				if (has_reflection)
				{
					state_reflec = state;
					atomic_inc(n_new_rays);
					state_reflec.ray = get_reflected_ray(state, hit_pos, normal);
					state_reflec.importance = state.importance * mats[obj.material_id].reflection;
					state_reflec.t = -1;
					state_reflec.obj_id = -1;
				}
		}
	}
	if (config->cur_depth < config->max_depth)
	{
		ray_states[gid] = state_reflec;
		ray_states[gid + config->screen_size.x * config->screen_size.y] = state_refrac;
	}
}

t_ray				get_reflected_ray(t_ray_state state, t_real3 hit_pos, t_real3 normal)
{
	t_ray		ray;

	ray.origin = hit_pos;
	ray.dir = state.ray.dir - (t_real)2 * dot(normal, state.ray.dir) * normal;
	return (ray);
}


t_ray				get_refracted_ray(t_ray_state state, t_real3 hit_pos, t_real3 normal, t_real ior)
{
	t_ray			ray;

	ray.origin = hit_pos + state.ray.dir * 0.001f; // bias
	if (dot(normal, state.ray.dir) < 0)
		ray.dir = -normal + (normal + state.ray.dir) * ior;
	else
		ray.dir = normal + (normal - state.ray.dir) * ior;
	return (ray);
}
