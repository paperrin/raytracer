#ifndef GET_SECONDARY_RAY_CL
# define GET_SECONDARY_RAY_CL

# include "host.h"

t_ray			get_reflected_ray(global t_config const *const config,
		t_ray ray, t_real3 hit_pos, t_real3 normal);
t_ray			get_refracted_ray(global t_config const *const config,
		t_obj *obj, t_ray ray, t_real3 hit_pos, t_real3 normal, t_real n2);


t_ray			get_reflected_ray(global t_config const *const config,
		t_ray ray, t_real3 hit_pos, t_real3 normal)
{
	t_ray		new_ray;

	new_ray.origin = hit_pos + normal * config->intersection_bias;
	new_ray.dir = ray.dir - (t_real)2 * dot(normal, ray.dir) * normal;
	return (new_ray);
}

t_ray			get_refracted_ray(global t_config const *const config,
		t_obj *obj, t_ray ray, t_real3 hit_pos, t_real3 normal, t_real n2)
{
	t_ray			new_ray;
	t_real			n1 = 1;
	t_real			cosi = dot(normal, -ray.dir);
	t_real			cosr = sqrt(1 - ((n1 / n2) * (n1 / n2)) * (1 - (cosi * cosi)));

	new_ray.origin = hit_pos - normal * config->intersection_bias;
	if (dot(obj_surface_normal_ext(obj, hit_pos), ray.dir) > 0)
	{
		n1 = n2;
		n2 = 1;
	}
	if (cosi <= 0.f)
		cosr = -cosr;
	new_ray.dir = (n1 / n2) * ray.dir + (n1 / n2 * cosi - cosr) * normal;
	return (new_ray);
}

#endif
