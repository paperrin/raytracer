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
		global t_config *config);
cl_float3			tone_map(cl_float3 color);

t_ray				get_reflected_ray(t_ray ray, t_real3 hit_pos, t_real3 normal);

cl_float3			get_specular_color_blinn(t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, cl_float3 light_color);

cl_float3			get_specular_color_phong(t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, cl_float3 light_color);

cl_float3			get_specular_color(t_e_shading_model shading_model, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, cl_float3 light_color);

cl_float3			get_specular_color(t_e_shading_model shading_model, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, cl_float3 light_color)
{
	if (shading_model == shading_model_blinn)
		return (get_specular_color_blinn(mat, view_dir, light_ray, hit_pos, surface_normal, light_color));
	return (get_specular_color_phong(mat, view_dir, light_ray, hit_pos, surface_normal, light_color));
}

cl_float3			tone_map(cl_float3 color)
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

cl_float3			get_specular_color_blinn(t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, cl_float3 light_color)
{
	cl_float3		h;
	cl_float		ndh;

	h = (-view_dir + light_ray.dir) / length(-view_dir + light_ray.dir);
	if (mat.specular > 39e-4)
	{
		ndh = dot(surface_normal, h);
		if (ndh >= 0)
			return (light_color * mat.specular * mat.specular_color * pow(ndh, mat.specular_exp));
	}
	return (0);
}

cl_float3			get_specular_color_phong(t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, cl_float3 light_color)
{
	cl_float		vdr;

	if (mat.specular > 39e-4)
	{
		if ((vdr =  dot(view_dir , get_reflected_ray(light_ray, hit_pos, surface_normal).dir)) > 0)
			return (light_color * mat.specular * mat.specular_color * pow(vdr, mat.specular_exp));
	}
	return (0);
}

cl_float3			shade(t_obj obj, t_real3 hit_pos, t_ray ray,
		constant t_obj *objs, cl_uint objs_size,
		constant t_material *mats, cl_uint mats_size,
		constant t_texture *textures, cl_uint textures_size,
		global cl_uchar *texture_pixels, cl_ulong n_texture_pixels,
		constant t_light *lights, cl_uint lights_size,
		global t_config *config)
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
			texture_pixf (shading_model == shading_model_blinn)
			 34         return (get_specular_color_blinn(mat, view_dir, light_ray, hit_pos, surface_normal, light_color));
			  35     return (get_specular_color_phong(mat, view_dir, light_ray, hit_pos, surface_normal, light_color));
			   36 }
			    37els, n_texture_pixels,
			hit_pos);
	color = surface_color * config->ambient;
	i = -1;
	while (++i < (int)lights_size)
	{
		light_ray.dir = light_get_dir(lights[i], hit_pos, &light_color, &light_dist);
		ndl = dot(light_ray.dir, surface_normal);
		if (ndl < 0)
			continue ;
		if (!(ray_throw_get_any_hit_obj(&light_ray, objs, objs_size, &t) > -1) || (light_dist <= t))
		{
			color += surface_color * light_color * (cl_float)ndl;
			color += get_specular_color(config->shading_model, mats[obj.material_id], ray.dir, light_ray, hit_pos, surface_normal, light_color);
		}
	}
	color = tone_map(color);
	return (color);
}

#endif
