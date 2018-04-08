#ifndef OBJ_SURFACE_NORMAL_CL
# define OBJ_SURFACE_NORMAL_CL

#include "shared.h"

t_real3			obj_surface_normal(t_obj *obj, t_real3 point, t_ray ray);
t_real3			obj_sphere_surface_normal(t_sphere *sphere, t_real3 point, t_ray ray);
t_real3			obj_plane_surface_normal(t_plane *plane, t_real3 point, t_ray ray);
t_real3			normal_reflect_ray(t_real3 normal, t_ray ray);
t_real3			obj_aligned_cube_surface_normal(t_aligned_cube *aligned_cube, t_real3 point, t_ray ray);

t_real3			normal_reflect_ray(t_real3 normal, t_ray ray)
{
	if (dot(normal, ray.dir) < 0)
		return (normal);
	return (-normal);
}

t_real3			obj_surface_normal(t_obj *obj, t_real3 point, t_ray ray)
{
	if (obj->type == type_sphere)
		return (obj_sphere_surface_normal(&obj->as.sphere, point, ray));
	else if (obj->type == type_plane)
		return (obj_plane_surface_normal(&obj->as.plane, point, ray));
	else if (obj->type == type_aligned_cube)
		return (obj_aligned_cube_surface_normal(&obj->as.aligned_cube, point, ray));
	return ((t_real3)(0, 0, 0));
}

t_real3			obj_aligned_cube_surface_normal(t_aligned_cube *aligned_cube, t_real3 point, t_ray ray)
{
	t_real3		normal;
	t_real3		extents;
	t_real3		dist;
	t_real		min;

	min = FLT_MAX;
	point -= aligned_cube->pos;// supposed to be center...
	extents = aligned_cube->size / 2; 
	dist = fabs(extents - fabs(point));
	if (dist.x < min)
	{
		min = dist.x;
		normal = (point.x > 0.0) ? (t_real3)(1, 0, 0) : (t_real3)(-1, 0, 0);
	}
	if (dist.y < min)
	{
		min = dist.y;
		normal = (point.y > 0.0) ? (t_real3)(0, 1, 0) : (t_real3)(0, -1, 0);
	}
	if (dist.z < min)
	{
		min = dist.z;
		normal = (point.z > 0.0) ? (t_real3)(0, 0, 1) : (t_real3)(0, 0, -1);
	}
	return (normal_reflect_ray(normal, ray));
}

t_real3			obj_sphere_surface_normal(t_sphere *sphere, t_real3 point, t_ray ray)
{
	t_real3		normal;

	normal = point - sphere->pos;
	normal = normalize(normal);
	return (normal_reflect_ray(normal, ray));
}

t_real3			obj_plane_surface_normal(t_plane *plane, t_real3 point, t_ray ray)
{
	return (normal_reflect_ray(plane->normal, ray));
}

#endif
