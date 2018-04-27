#ifndef OBJ_RAY_HIT_CL
# define OBJ_RAY_HIT_CL

# include "host.h"

cl_int			ray_throw_get_first_hit_obj(global t_config const *const config, t_ray *ray,
		constant t_obj *objs, cl_uint objs_size, t_real *t_nearest);
cl_int			ray_throw_get_any_hit_obj(global t_config const *const config, t_ray *ray,
		constant t_obj *objs, cl_uint objs_size, t_real *t);

t_real			obj_ray_hit(
		constant t_obj const *const obj, t_ray *ray);
t_real			obj_sphere_ray_hit(
		constant t_obj const *const obj, t_ray *ray);
t_real			obj_aligned_cube_ray_hit(
		constant t_obj const *const obj, t_ray *ray);
t_real			obj_plane_ray_hit(
		constant t_obj const *const obj, t_ray *ray);
t_real			obj_cylinder_ray_hit(
		constant t_obj const *const obj, t_ray *ray);
t_real			obj_cone_ray_hit(
		constant t_obj const *const obj, t_ray *ray);

t_real			solve_quadratic(t_real3 abc, t_real *values);

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

cl_int			ray_throw_get_first_hit_obj(global t_config const *const config, t_ray *ray,
		constant t_obj *objs, cl_uint objs_size, t_real *t_nearest)
{
	t_real		t;
	cl_int		i;
	cl_int		obj_id_nearest;

	i = -1;
	*t_nearest = config->z_far;
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

cl_int			ray_throw_get_any_hit_obj(global t_config const *const config, t_ray *ray,
		constant t_obj *objs, cl_uint objs_size, t_real *t)
{
	cl_int		i;

	*t = config->z_far;
	i = -1;
	while (++i < (t_obj_id)objs_size)
	{
		if ((*t = obj_ray_hit(&objs[i], ray)) >= 0)
			return (i);
	}
	return (-1);
}

t_real			obj_ray_hit(constant t_obj const *const obj,
		t_ray *ray)
{
	if (obj->type == e_type_sphere)
		return (obj_sphere_ray_hit(obj, ray));
	else if (obj->type == e_type_plane)
		return (obj_plane_ray_hit(obj, ray));
	else if (obj->type == e_type_cone)
		return (obj_cone_ray_hit(obj, ray));
	else if (obj->type == e_type_cylinder)
			return (obj_cylinder_ray_hit(obj, ray));
	else if (obj->type == e_type_aligned_cube)
		return (obj_aligned_cube_ray_hit(obj, ray));
	else
		return (-1);
}

t_real			obj_plane_ray_hit(constant t_obj const *const obj, t_ray *ray)
{
	t_real		denom;
	t_real		t;
	t_real3		p;

	denom =	dot(obj->up, ray->dir);
	if (fabs(denom) > 1e-10)
	{
		p = obj->pos - ray->origin;
		t = dot(obj->up, p) / denom;
		return (t);
	}
	return (-1);
}

t_real			obj_sphere_ray_hit(constant t_obj const *const obj, t_ray *ray)
{
	t_real3		dist;
	t_real3		abc;
	t_real		hits[2];

	dist = ray->origin - obj->pos;
	abc[0] = dot(ray->dir, ray->dir);
	abc[1] = 2 * dot(ray->dir, dist);
	abc[2] = dot(dist, dist) - obj->as.sphere.radius * obj->as.sphere.radius;
	if (solve_quadratic(abc, hits) < 0)
		return (-1);
	return (hits[0]);
}

t_real		obj_cone_ray_hit(constant t_obj const *const obj, t_ray *ray)
{
	t_real3     abc;
	t_real      hits[2];
	t_real      tan_a;
	t_real3     dp;

	dp = ray->origin - obj->pos;
	tan_a = tan(obj->as.cone.angle);
	abc[0] = dot(ray->dir, ray->dir) - (1 + tan_a * tan_a) * dot(ray->dir, obj->up) * dot(ray->dir, obj->up);
	abc[1] = (dot(ray->dir, dp) - (1 + tan_a * tan_a) * dot(ray->dir, obj->up) * dot(dp, obj->up)) * (t_real)2;
	abc[2] = dot(dp, dp) - (1 + tan_a * tan_a) * dot(dp, obj->up) * dot(dp, obj->up);
	if (solve_quadratic(abc, hits) < 0)
		return (-1);
	return (hits[0]);
}

t_real				obj_cylinder_ray_hit(constant t_obj const *const obj, t_ray *ray)
{
	t_real3			abc;
	t_real			hits[2];
	t_real3			diff;

	diff = ray->origin - obj->pos;
	abc[0] = dot(ray->dir, ray->dir) - dot(ray->dir, obj->up) * dot(ray->dir, obj->up);
	abc[1] = dot(ray->dir, diff) - dot(ray->dir, obj->up) * dot(diff, obj->up);
	abc[1] *= 2;
	abc[2] = dot(diff, diff) - dot(diff, obj->up) * dot(diff, obj->up)
		- obj->as.cylinder.radius * obj->as.cylinder.radius;
	if (solve_quadratic(abc, hits) < 0)
		return (-1);
	return (hits[0]);
}

t_real			obj_aligned_cube_ray_hit(constant t_obj const *const obj, t_ray *ray)
{
	t_real		t1;
	t_real		t2;
	t_real		t_min;
	t_real		t_max;
	t_real3		invdir;
	t_real3		box_center;

	t_min = -INFINITY;
	t_max = +INFINITY;
	invdir = 1 / ray->dir;
	box_center = obj->pos - obj->as.aligned_cube.size / 2;
	t1 = (box_center.x - ray->origin.x) * invdir.x;
	t2 = (box_center.x + obj->as.aligned_cube.size.x - ray->origin.x) * invdir.x;
	t_min = fmax(fmin(t1, t2), t_min);
	t_max = fmin(fmax(t1, t2), t_max);

	t1 = (box_center.y - ray->origin.y) * invdir.y;
	t2 = (box_center.y + obj->as.aligned_cube.size.y - ray->origin.y) * invdir.y;
	t_min = fmax(fmin(t1, t2), t_min);
	t_max = fmin(fmax(t1, t2), t_max);

	t1 = (box_center.z - ray->origin.z) * invdir.z;
	t2 = (box_center.z + obj->as.aligned_cube.size.z - ray->origin.z) * invdir.z;
	t_min = fmax(fmin(t1, t2), t_min);
	t_max = fmin(fmax(t1, t2), t_max);
	if (t_min < t_max)
		return ((t_min < FLT_MIN) ? t_max : t_min);
	else
		return (-1);
}

#endif
