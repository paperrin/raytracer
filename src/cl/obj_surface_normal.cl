#ifndef OBJ_SURFACE_NORMAL_CL
# define OBJ_SURFACE_NORMAL_CL

#include "shared.h"

t_real3			obj_surface_normal(t_obj const *const obj, t_real3 point, t_ray ray);
t_real3			obj_surface_normal_ext(t_obj const *const obj, t_real3 point);

t_real3			obj_cone_surface_normal(t_obj const *const obj, t_real3 point);
t_real3			obj_sphere_surface_normal(t_obj const *const obj, t_real3 point);
t_real3			obj_cylinder_surface_normal(t_obj const *const obj, t_real3 point);
t_real3			obj_aligned_cube_surface_normal(t_obj const *const obj, t_real3 point);
t_real3			obj_plane_surface_normal(t_obj const *const obj, t_real3 point);

t_real3			normal_reflect_ray(t_real3 normal, t_ray ray);

t_real3			normal_reflect_ray(t_real3 normal, t_ray ray)
{
	if (dot(normal, ray.dir) < 0)
		return (normal);
	return (-normal);
}

t_real3			obj_surface_normal(t_obj const *const obj, t_real3 point, t_ray ray)
{
	return (normal_reflect_ray(obj_surface_normal_ext(obj, point), ray));
}

t_real3			obj_surface_normal_ext(t_obj const *const obj, t_real3 point)
{
	if (obj->type == e_type_sphere)
		return (obj_sphere_surface_normal(obj, point));
	else if (obj->type == e_type_plane)
		return (obj_plane_surface_normal(obj, point));
	else if (obj->type == e_type_aligned_cube)
		return (obj_aligned_cube_surface_normal(obj, point));
	else if (obj->type == e_type_cone)
		return (obj_cone_surface_normal(obj, point));
	else if (obj->type == e_type_cylinder)
		return (obj_cylinder_surface_normal(obj, point));
	return ((t_real3)(0, 0, 0));
}

t_real3			obj_cone_surface_normal(t_obj const *const obj, t_real3 point)
{
	t_real3		normal;
	t_real3		surface_tangeant;
	t_real3		rel_pos;

	rel_pos = point - obj->pos;
	surface_tangeant = cross(rel_pos, obj->up);
	normal = cross(rel_pos, surface_tangeant);
	normal = normalize(normal);
	return (normal);
}

t_real3			obj_cylinder_surface_normal(t_obj const *const obj, t_real3 point)
{
	t_real3		normal;
	t_real3		surface_tangeant;
	t_real3		rel_pos;

	rel_pos = point - obj->pos;
	surface_tangeant = cross(rel_pos, obj->up);
	normal = cross(obj->up, surface_tangeant);
	normal = normalize(normal);
	return (normal);
}

t_real3			obj_aligned_cube_surface_normal(t_obj const *const obj, t_real3 point)
{
	t_real3		normal;
	t_real3		extents;
	t_real3		dist;
	t_real		min;

	min = FLT_MAX;
	point -= obj->pos;
	extents = obj->as.aligned_cube.size / 2;
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
	return (normal);
}

t_real3			obj_sphere_surface_normal(t_obj const *const obj, t_real3 point)
{
	t_real3		normal;

	normal = point - obj->pos;
	normal = normalize(normal);
	return (normal);
}

t_real3			obj_plane_surface_normal(t_obj const *const obj, t_real3 point)
{
	return (obj->up);
}

#endif
