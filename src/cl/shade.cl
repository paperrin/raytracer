#ifndef SHADE_CL
# define SHADE_CL

#include "shared.h"
#include "obj_ray_hit.cl"
#include "obj_surface_normal.cl"
#include "obj_surface_color.cl"
#include "light_get_dir.cl"

float3			shade(t_obj obj, t_real3 hit_pos, t_ray ray,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		constant t_light *lights, uint lights_size,
		global t_config *config);
float3			tone_map(float3 color);

t_ray				get_reflected_ray(t_ray ray, t_real3 hit_pos, t_real3 normal);

float3			get_specular_color_blinn(t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color);

float3			get_specular_color_phong(t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color);

float3			get_specular_color(t_e_shading_model shading_model, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color);

int			is_in_shadow(float3 *perceived_l_color, t_ray light_ray, float3 light_color, t_real light_dist,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels ,global t_config *config);

float3			get_specular_color(t_e_shading_model shading_model, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color)
{
	if (shading_model == shading_model_blinn)
		return (get_specular_color_blinn(mat, view_dir, light_ray, hit_pos, surface_normal, light_color));
	return (get_specular_color_phong(mat, view_dir, light_ray, hit_pos, surface_normal, light_color));
}

float3			tone_map(float3 color)
{
	color.r = color.r / (color.r + 1);
	color.g = color.g / (color.g + 1);
	color.b = color.b / (color.b + 1);
	return (color);
}

t_ray				get_reflected_ray(t_ray ray, t_real3 hit_pos, t_real3 normal)
{
	t_ray		new_ray;

	new_ray.origin = hit_pos;
	new_ray.dir = ray.dir - (t_real)2 * dot(normal, ray.dir) * normal;
	return (new_ray);
}

float3			get_specular_color_blinn(t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color)
{
	float3		h;
	float		ndh;

	h = (-view_dir + light_ray.dir) / length(-view_dir + light_ray.dir);
	if (mat.specular > 39e-4)
	{
		ndh = dot(surface_normal, h);
		if (ndh >= 0)
			return (light_color * mat.specular * mat.specular_color * pow(ndh, mat.specular_exp));
	}
	return (0);
}

float3			get_specular_color_phong(t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color)
{
	float		vdr;

	if (mat.specular > 39e-4)
	{
		if ((vdr =  dot(view_dir , get_reflected_ray(light_ray, hit_pos, surface_normal).dir)) > 0)
			return (light_color * mat.specular * mat.specular_color * pow(vdr, mat.specular_exp));
	}
	return (0);
}

int			is_in_shadow(float3 *perceived_l_color, t_ray light_ray, float3 light_color, t_real light_dist,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels, global t_config *config)
{
	float				importance = 1;
	t_real				t;
	t_obj_id			obj_id;
	t_real3				hit_pos;
	constant t_material	*mat;
	t_obj				obj;

	*perceived_l_color = (float3)(1);
		while ((obj_id = ray_throw_get_first_hit_obj(&light_ray, objs, objs_size, &t)) > -1 && light_dist > t)
		{
			obj = objs[obj_id];
			mat = &mats[obj.material_id];
			importance *= mat->refraction;
			if (importance < 1.f/255)
				return (1);
			hit_pos = light_ray.origin + light_ray.dir * t;
			*perceived_l_color *= obj_surface_color(&obj, mats, textures, textures_size,
					texture_pixels, n_texture_pixels, hit_pos) * importance;
			light_ray.origin = hit_pos + obj_surface_normal(&obj, hit_pos, light_ray) * (t_real)-1e-3;
			light_dist -= t + t * 1e-3;
		}
		*perceived_l_color *= light_color * importance;
	return (0);
}

float3			shade(t_obj obj, t_real3 hit_pos, t_ray ray,
		constant t_obj *objs, uint objs_size,
		constant t_material *mats, uint mats_size,
		constant t_texture *textures, uint textures_size,
		global uchar *texture_pixels, ulong n_texture_pixels,
		constant t_light *lights, uint lights_size,
		global t_config *config)
{
	t_real3			surface_normal;
	t_ray			light_ray;
	float3		light_color;
	float3		color;
	int				i;
	t_real			ndl;
	t_real			light_dist;
	float3		surface_color;
	float3		perceived_l_color;

	surface_normal = obj_surface_normal(&obj, hit_pos, ray);
	light_ray.origin = hit_pos;
	surface_color = obj_surface_color(
			&obj,
			mats,
			textures, textures_size,
			texture_pixels, n_texture_pixels,
			hit_pos);
	color = surface_color * config->ambient;
	i = -1;
	while (++i < (int)lights_size)
	{
		light_ray.dir = light_get_dir(lights[i], hit_pos, &light_color, &light_dist);
		ndl = dot(light_ray.dir, surface_normal);
		if (ndl < 0)
			continue ;
		if (!is_in_shadow(&perceived_l_color, light_ray, light_color, light_dist, objs, objs_size, mats,
					mats_size, textures, textures_size, texture_pixels, n_texture_pixels, config))
		{
			color += surface_color * perceived_l_color * (float)ndl;
			color += get_specular_color(config->shading_model, mats[obj.material_id], ray.dir, light_ray, hit_pos, surface_normal, perceived_l_color);
		}
	}
	color = tone_map(color);
	return (color);
}

#endif
