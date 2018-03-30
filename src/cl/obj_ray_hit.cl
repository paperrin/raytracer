#include "shared.h"

t_real				solve_quadratic(t_real3 abc, t_real *values);
t_real				obj_ray_hit(constant t_obj *obj,
		t_ray *ray);
t_real				obj_sphere_ray_hit(constant t_sphere *sphere,
		t_ray *ray);
t_real				obj_aligned_cube_ray_hit(constant t_aligned_cube *aligned_cube,
		t_ray *ray);

cl_int				ray_throw_get_first_hit_obj(t_ray *ray,
		constant t_obj *objs, cl_uint objs_size, t_real *t_nearest);
cl_int			ray_throw_get_any_hit_obj(t_ray *ray,
		constant t_obj *objs, cl_uint objs_size, t_real *t);
t_real				obj_plane_ray_hit(constant t_plane *plane, t_ray *ray);
t_real				has_hit(constant t_aligned_cube *aligned_cube, t_ray *ray, t_real3 *intersect);

t_real			solve_quadratic(t_real3 abc, t_real *values)
{
	t_real		discr;
	t_real		sq_discr;
	t_real		tmp;

	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (-1);
	sq_discr = sqrt(discr);
	values[0] = (-abc[1] - sq_discr) / (2 * abc[0]);
	values[1] = (-abc[1] + sq_discr) / (2 * abc[0]);
	if (values[1] < values[0])
	{
		tmp = values[1];
		values[1] = values[0];
		values[0] = tmp;
	}
	if (values[0] < 0)
	{
		tmp = values[1];
		values[1] = values[0];
		values[0] = tmp;
	}	
	return (discr);
}

cl_int			ray_throw_get_first_hit_obj(t_ray *ray,
		constant t_obj *objs, cl_uint objs_size, t_real *t_nearest)
{
	t_real		t;
	cl_int		i;
	cl_int		obj_id_nearest;

	i = -1;
	*t_nearest = 200000;
	obj_id_nearest = -1;
	while (++i < (t_obj_id)objs_size)
	{
		if ((t = obj_ray_hit(&objs[i], ray)) >= 0 && t < *t_nearest)
		{
			*t_nearest = t;
			obj_id_nearest = i;
		}
	}
	return (obj_id_nearest);
}

cl_int			ray_throw_get_any_hit_obj(t_ray *ray,
		constant t_obj *objs, cl_uint objs_size, t_real *t)
{
	cl_int		i;

	*t = 200000;
	i = -1;
	while (++i < (t_obj_id)objs_size)
	{
		if ((*t = obj_ray_hit(&objs[i], ray)) >= 0)
			return (i);
	}
	return (-1);
}

t_real			obj_ray_hit(constant t_obj *obj,
		t_ray *ray)
{
	printf("ray [%f|%f]\n", (float)ray->dir.y, (float)ray->dir.x);
	if (obj->type == type_sphere)
		return (obj_sphere_ray_hit(&obj->as.sphere, ray));
	else if (obj->type == type_plane)
		return (obj_plane_ray_hit(&obj->as.plane, ray));
/*	else if (obj->type == type_aligned_cube)
		return (obj_aligned_cube_ray_hit(&obj->as.aligned_cube, ray));*/
	else
		return (-1);
}

t_real			obj_plane_ray_hit(constant t_plane *plane, t_ray *ray)
{
	t_real		denom;
	t_real		t;
	t_real3		p;

	denom =	dot(plane->normal, ray->dir);
	if (fabs(denom) > 1e-10)
	{
		p = plane->pos - ray->origin;
		t = dot(plane->normal, p) / denom;
		return (t);
	}
	return (-1);
}

t_real			obj_sphere_ray_hit(constant t_sphere *sphere, t_ray *ray)
{
	t_real3		dist;
	t_real3		abc;
	t_real		hits[2];

	dist = ray->origin - sphere->pos;
	abc[0] = dot(ray->dir, ray->dir);
	abc[1] = 2 * dot(ray->dir, dist);
	abc[2] = dot(dist, dist) - sphere->radius * sphere->radius;
	if (solve_quadratic(abc, hits) < 0)
		return (-1);
	return (hits[0]);
}
/*
t_real		has_hit(constant t_aligned_cube *aligned_cube, t_ray *ray, t_real3 *intersect)
{
	t_real		slope;
	
if (fabs(ray->dir.y) > 0.f && fabs(ray->dir.x) > 0.f)
		slope = ray->dir.y / ray->dir.x;
	else if (fabs(ray->dir.y) > 0.f)
		slope = ray->dir.y;
	else if (fabs(ray->dir.x) > 0.f)
		slope = ray->dir.x;
	else
		slope = 0.f;
	if (fabs(slope) > 0.f)
	{
		intersect->z = aligned_cube->pos.z;
		intersect->y = aligned_cube->pos.y;
		intersect->x = (intersect->y - ray->origin.y) / slope;
		if (intersect->x >= aligned_cube->pos.x && intersect->x <= (aligned_cube->pos.x + aligned_cube->size.x))
			return (0);
		else
			return (1);
	}
	return (0);
}

t_real		obj_aligned_cube_ray_hit(constant t_aligned_cube *aligned_cube, t_ray *ray)
{
	t_real3	dist;
	t_real	i;

	dist = aligned_cube->pos - ray->origin;
	printf("before | diry %f | dirx %f\n", ray->dir.y, ray->dir.x);
	i = has_hit(aligned_cube, ray, &intersect);
	return (-1);
}*/
