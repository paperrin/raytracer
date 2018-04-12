#ifndef SHADE_CL
# define SHADE_CL

#include "shared.h"
#include "obj_ray_hit.cl"
#include "obj_surface_normal.cl"
#include "obj_surface_color.cl"
#include "light_get_dir.cl"
#include "get_specular_color.cl"

float3			shade(global t_config const *const config, t_obj obj, t_real3 hit_pos, t_ray ray,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		constant t_light *lights, uint lights_size);

float3			tone_map(float3 color);

int				is_in_shadow(global t_config const *const config, float3 *perceived_l_color, t_ray light_ray, float3 light_color, t_real light_dist,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels);

float3			tone_map(float3 color)
{
	color.r = color.r / (color.r + 1);
	color.g = color.g / (color.g + 1);
	color.b = color.b / (color.b + 1);
	return (color);
}

int			is_in_shadow(global t_config const *const config, float3 *perceived_l_color, t_ray light_ray, float3 light_color, t_real light_dist,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels)
{
	float				importance = 1;
	t_real				t;
	t_obj_id			obj_id;
	t_real3				hit_pos;
	constant t_material	*mat;
	t_obj				obj;
	cl_uint				p_depth = 0;

	if (!config->projection_depth && ray_throw_get_any_hit_obj(config, &light_ray, objs, objs_size, &t) > -1 && light_dist > t)
		return (1);
	*perceived_l_color = (float3)(1, 1, 1);
	while ((obj_id = ray_throw_get_first_hit_obj(config, &light_ray, objs, objs_size, &t)) > -1 && light_dist > t)
	{
		obj = objs[obj_id];
		mat = &mats[obj.material_id];
		importance *= mat->refraction;
		if (p_depth >= config->projection_depth || !mat->projection
				|| importance < config->color_epsilon)
			return (1);
		hit_pos = light_ray.origin + light_ray.dir * t;
		*perceived_l_color *= obj_surface_color(&obj, mats, textures, textures_size,
				texture_pixels, n_texture_pixels, hit_pos) * importance;
		light_ray.origin = hit_pos + obj_surface_normal(&obj, hit_pos, light_ray) * (t_real)-config->intersection_bias;
		light_dist -= t + t * config->intersection_bias;
		p_depth++;
	}
	return (0);
}

float3			shade(global t_config const *const config, t_obj obj, t_real3 hit_pos, t_ray ray,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		constant t_light *lights, uint lights_size)
{
	t_real3			surface_normal;
	t_ray			light_ray;
	float3			light_color;
	float3			color;
	int				i;
	t_real			ndl;
	t_real			light_dist;
	float3			surface_color;
	float3			perceived_l_color;
	float			vdn;

	surface_normal = obj_surface_normal(&obj, hit_pos, ray);
	light_ray.origin = hit_pos;
	surface_color = obj_surface_color(
			&obj,
			mats,
			textures, textures_size,
			texture_pixels, n_texture_pixels,
			hit_pos);
	color = (float3)(0, 0, 0);
	vdn = dot(-surface_normal, ray.dir);
	i = -1;
	while (++i < (int)lights_size)
	{
		light_ray.dir = light_get_dir(config, lights[i], hit_pos, &light_color, &light_dist);
		ndl = dot(light_ray.dir, surface_normal);
		if (ndl < 0)
			continue ;
		if (!is_in_shadow(config, &perceived_l_color, light_ray, light_color, light_dist, objs, objs_size, mats,
					mats_size, textures, textures_size, texture_pixels, n_texture_pixels))
		{
			color += surface_color * perceived_l_color * light_color * (float)ndl;
			color += get_specular_color(config, mats[obj.material_id], ray.dir, light_ray, hit_pos, surface_normal, perceived_l_color * light_color);
		}
	}
	color += surface_color * config->camera_light_c * config->camera_light_i * vdn;
	color += surface_color * config->ambient_c * config->ambient_i;
	color = tone_map(color);
	return (color);
}

#endif
