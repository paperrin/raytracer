#ifndef SHADE_CL
# define SHADE_CL

#include "host.h"
#include "obj_ray_hit.cl"
#include "obj_surface_normal.cl"
#include "obj_surface_color.cl"
#include "light_get_dir.cl"
#include "get_specular_color.cl"

float3			shade(
		global t_config const *const config,
		t_obj obj, t_real3 hit_pos, t_real3 normal,
		float3 surface_color, float surface_refraction,
		t_ray ray,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		constant t_light *lights, uint lights_size);

float3			tone_map(float3 color);
float3			mix_colors(float3 color1, float3 color2, float ratio);

int				is_in_shadow(global t_config const *const config, float3 *perceived_l_color, t_ray light_ray, float3 light_color, t_real light_dist,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels);

float3			tone_map(float3 color)
{
	color = fabs(atan(color));
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
	float				surface_refraction;
	float3				surface_color;

	*perceived_l_color = (float3)(1, 1, 1);
	while ((obj_id = ray_throw_get_first_hit_obj(config, &light_ray, objs, objs_size, &t)) > -1 && light_dist > t)
	{
		obj = objs[obj_id];
		mat = &mats[obj.material_id];
		hit_pos = light_ray.origin + light_ray.dir * t;
		light_ray.origin = hit_pos + obj_surface_normal(&obj, hit_pos, light_ray) * (t_real)-config->intersection_bias;
		light_dist -= t + t * config->intersection_bias;
		if (mat->ignores_light)
			continue ;
		surface_refraction = obj_surface_refraction(&obj, mats, textures, textures_size,
				texture_pixels, n_texture_pixels, hit_pos);
		importance *= surface_refraction;
		if (p_depth >= config->projection_depth || !mat->projection
				|| importance < config->color_epsilon)
			return (1);
		surface_color = obj_surface_color(&obj, mats, textures, textures_size, texture_pixels, n_texture_pixels, hit_pos);
		*perceived_l_color = *perceived_l_color * surface_color * surface_refraction;
		p_depth++;
	}
	return (0);
}

float3			shade(
		global t_config const *const config,
		t_obj obj, t_real3 hit_pos, t_real3 normal,
		float3 surface_color, float surface_refraction,
		t_ray ray,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		constant t_light *lights, uint lights_size)
{
	t_ray			light_ray;
	float3			light_color;
	float3			color;
	int				i;
	t_real			ndl;
	t_real			light_dist;
	float3			perceived_l_color;
	float			vdn;

	color = (float3)(0, 0, 0);
	i = -1;
	if (!mats[obj.material_id].ignores_light)
	{
		light_ray.origin = hit_pos + normal * config->intersection_bias;
		vdn = dot(-normal, ray.dir);
		while (++i < (int)lights_size)
		{
			light_ray.dir = light_get_dir(config, lights[i], hit_pos, &light_color, &light_dist);
			ndl = dot(light_ray.dir, normal);
			if (ndl > 0 && !is_in_shadow(config, &perceived_l_color, light_ray, light_color, light_dist, objs, objs_size, mats,
						mats_size, textures, textures_size, texture_pixels, n_texture_pixels))
			{
				color += surface_color * perceived_l_color * light_color * (float)ndl;
				color += get_specular_color(config, mats[obj.material_id], ray.dir, light_ray, hit_pos, normal, perceived_l_color * light_color);
			}
		}
		color += surface_color * config->camera_light_c * config->camera_light_i * vdn;
		color += surface_color * config->ambient_c * config->ambient_i;
	}
	color += surface_color * mats[obj.material_id].emission;
	color = tone_map(color);
	return (color);
}

#endif
