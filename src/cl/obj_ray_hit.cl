#include "shared.h"

t_real				solve_quadratic(t_real3 abc, t_real *values);
t_real				obj_ray_hit(constant t_obj *obj,
		global t_ray *ray);
t_real				obj_sphere_ray_hit(constant t_sphere *sphere,
		global t_ray *ray);

t_real			solve_quadratic(t_real3 abc, t_real *values)
{
	t_real		discr;
	t_real		tmp;

	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (-1);
	discr = sqrt(discr);
	values[0] = (-abc[1] - discr) / (2 * abc[0]);
	values[1] = (-abc[1] + discr) / (2 * abc[0]);
	if (values[1] < values[0])
	{
		tmp = values[1];
		values[1] = values[0];
		values[0] = tmp;
	}
	return (discr);
}

t_real			obj_ray_hit(constant t_obj *obj,
		global t_ray *ray)
{
	if (obj->type == type_sphere)
		return (obj_sphere_ray_hit(&obj->as.sphere, ray));
	else
		return (-1);
}

t_real			obj_sphere_ray_hit(constant t_sphere *sphere,
		global t_ray *ray)
{
	t_real3		dist;
	t_real3		abc;
	t_real		hits[2];

	dist = ray->origin - sphere->pos;
	abc[0] = dot(ray->dir, ray->dir);
	abc[1] = 2 * dot(ray->dir, dist);
	abc[2] = dot(dist, dist) - sphere->radius * sphere->radius;
	if (solve_quadratic(abc, hits) < 0 || hits[0] < 0)
		return (-1);
	return (hits[0]);
}
