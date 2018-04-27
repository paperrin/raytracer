#ifndef GET_SPECULAR_COLOR_CL
# define GET_SPECULAR_COLOR_CL

# include "host.h"
# include "obj_ray_hit.cl"
# include "get_secondary_ray.cl"

float3			get_specular_color(global t_config const *const config, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color);
float3			get_specular_color_blinn(global t_config const *const config, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color);
float3			get_specular_color_phong(global t_config const *const config, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color);

float3			get_specular_color(global t_config const *const config, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color)
{
	if (config->shading_model == e_shading_model_blinn)
		return (get_specular_color_blinn(config, mat, view_dir, light_ray, hit_pos, surface_normal, light_color));
	return (get_specular_color_phong(config, mat, view_dir, light_ray, hit_pos, surface_normal, light_color));
}

float3			get_specular_color_blinn(global t_config const *const config, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color)
{
	t_real3		h;
	float		ndh;

	h = (-view_dir + light_ray.dir) / length(-view_dir + light_ray.dir);
	if (mat.specular > config->color_epsilon)
	{
		ndh = dot(surface_normal, h);
		if (ndh > 0)
			return (light_color * mat.specular * mat.specular_color * pow(ndh, mat.specular_exp));
	}
	return ((float3)(0,0,0));
}

float3			get_specular_color_phong(global t_config const *const config, t_material mat, t_real3 view_dir,
		t_ray light_ray, t_real3 hit_pos, t_real3 surface_normal, float3 light_color)
{
	float		vdr;

	if (mat.specular > config->color_epsilon)
	{
		if ((vdr = dot(view_dir , get_reflected_ray(config, light_ray, hit_pos, surface_normal).dir)) > 0)
			return (light_color * mat.specular * mat.specular_color * pow(vdr, mat.specular_exp));
	}
	return ((float3)(0,0,0));
}

#endif
