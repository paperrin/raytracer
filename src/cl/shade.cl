#ifndef SHADE_CL
# define SHADE_CL

#include "shared.h"
#include "obj_ray_hit.cl"
#include "obj_surface_normal.cl"
#include "obj_surface_color.cl"
#include "light_get_dir.cl"

cl_float3			shade(t_obj obj, t_real3 hit_pos, t_ray ray,
		constant t_obj *objs, cl_uint objs_size,
		constant t_material *mats, cl_uint mats_size,
		constant t_texture *textures, cl_uint textures_size,
		global cl_uchar *texture_pixels, cl_ulong n_texture_pixels,
		constant t_light *lights, cl_uint lights_size,
		cl_float3 ambient);
cl_float3			tone_map(cl_float3 color);

cl_float3			tone_map(cl_float3 color)
{
	color.r = color.r / (color.r + 1);
	color.g = color.g / (color.g + 1);
	color.b = color.b / (color.b + 1);
	return (color);
}

cl_float3			shade(t_obj obj, t_real3 hit_pos, t_ray ray,
		constant t_obj *objs, cl_uint objs_size,
		constant t_material *mats, cl_uint mats_size,
		constant t_texture *textures, cl_uint textures_size,
		global cl_uchar *texture_pixels, cl_ulong n_texture_pixels,
		constant t_light *lights, cl_uint lights_size,
		cl_float3 ambient)
{
	t_real3			surface_normal;
	t_ray			light_ray;
	cl_float3		light_color;
	t_real			t;
	cl_float3		color;
	int				i;
	t_real			ndl;
	t_real			light_dist;
	cl_float3		surface_color;

	surface_normal = obj_surface_normal(&obj, hit_pos, ray);
	light_ray.origin = hit_pos;
	surface_color = obj_surface_color(
			&obj,
			mats,
			textures, textures_size,
			texture_pixels, n_texture_pixels,
			hit_pos);
	color = surface_color * ambient;
	i = -1;
	while (++i < (int)lights_size)
	{
		light_ray.dir = light_get_dir(lights[i], hit_pos, &light_color, &light_dist);
		ndl = dot(light_ray.dir, surface_normal);
		if (ndl < 0)
			continue ;
		if (!(ray_throw_get_any_hit_obj(&light_ray, objs, objs_size, &t) > -1) || (light_dist <= t))
			color += surface_color * light_color * (cl_float)ndl;
	}
	color = tone_map(color);
	return (color);
}

#endif
