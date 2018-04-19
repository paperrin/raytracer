#ifndef OBJ_SURFACE_NORMAL_CL
# define OBJ_SURFACE_NORMAL_CL

#include "shared.h"
#include "host.h"

t_real3			obj_surface_normal_ext(t_obj *obj, t_real3 point);
t_real3			obj_surface_normal(t_obj *obj, t_real3 point, t_ray ray);
t_real3			obj_sphere_surface_normal(t_sphere *sphere, t_real3 point);
t_real3			obj_plane_surface_normal(t_plane *plane, t_real3 point);
t_real3			normal_reflect_ray(t_real3 normal, t_ray ray);
t_real3			obj_aligned_cube_surface_normal(t_aligned_cube *aligned_cube, t_real3 point);

t_real3			normal_reflect_ray(t_real3 normal, t_ray ray)
{
	if (dot(normal, ray.dir) < 0)
		return (normal);
	return (-normal);
}

t_real3			obj_surface_normal(t_obj *obj, t_real3 point, t_ray ray)
{
	return (normal_reflect_ray(obj_surface_normal_ext(obj, point), ray));
}

t_real3			obj_surface_normal_ext(t_obj *obj, t_real3 point)
{
	if (obj->type == e_type_sphere)
		return (obj_sphere_surface_normal(&obj->as.sphere, point));
	else if (obj->type == e_type_plane)
		return (obj_plane_surface_normal(&obj->as.plane, point));
	else if (obj->type == e_type_aligned_cube)
		return (obj_aligned_cube_surface_normal(&obj->as.aligned_cube, point));
	return ((t_real3)(0, 0, 0));
}

t_real3			obj_aligned_cube_surface_normal(t_aligned_cube *aligned_cube, t_real3 point)
{
	t_real3		normal;
	t_real3		dist;
	t_real		min;

	min = FLT_MAX;
	point -= aligned_cube->pos;
	dist = fabs(aligned_cube->size / 2 - fabs(point));
	min = fmin(dist.x, fmin(dist.y, dist.z));

	normal.x = (min == dist.x) * ((point.x > 0) * 2 - 1);
	normal.y = (min == dist.y) * ((point.y > 0) * 2 - 1);
	normal.z = (min == dist.z) * ((point.z > 0) * 2 - 1);
	return (normalize(normal));
}

t_real3			obj_sphere_surface_normal(t_sphere *sphere, t_real3 point)
{
	t_real3		normal;

	normal = point - sphere->pos;
	normal = normalize(normal);
	return (normal);
}

t_real3			obj_plane_surface_normal(t_plane *plane, t_real3 point)
{
	return (plane->normal);
}

#endif
