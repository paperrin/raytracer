#ifndef GET_SECONDARY_RAY_CL
# define GET_SECONDARY_RAY_CL

# include "shared.h"

t_ray			get_reflected_ray(global t_config const *const config,
		t_ray ray, t_real3 hit_pos, t_real3 nomal);
t_ray			get_refracted_ray(global t_config const *const config,
		t_ray ray, t_real3 hit_pos, t_real3 normal, t_real ior);


t_ray			get_reflected_ray(global t_config const *const config,
		t_ray ray, t_real3 hit_pos, t_real3 normal)
{
	t_ray		new_ray;

	new_ray.origin = hit_pos;
	new_ray.dir = ray.dir - (t_real)2 * dot(normal, ray.dir) * normal;
	return (new_ray);
}

t_ray			get_refracted_ray(global t_config const *const config,
		t_ray ray, t_real3 hit_pos, t_real3 normal, t_real ior)
{
	t_ray			new_ray;

	new_ray.origin = hit_pos - normal * config->intersection_bias * 2;
	if (dot(normal, ray.dir) < 0)
		new_ray.dir = -normal + (normal + ray.dir) * ior;
	else
		new_ray.dir = normal + (normal - ray.dir) * ior;
	return (new_ray);
}

#endif
