#ifndef OBJ_SURFACE_NORMAL_CL
# define OBJ_SURFACE_NORMAL_CL

#include "shared.h"

t_real3			obj_surface_normal(t_obj *obj, t_real3 point);
t_real3			obj_sphere_surface_normal(t_sphere *sphere, t_real3 point);
t_real3			obj_plane_surface_normal(t_plane *plane, t_real3 point);
t_real3			obj_cylinder_surface_normal(t_cylinder *cylinder, t_real3 point);

t_real3			obj_surface_normal(t_obj *obj, t_real3 point)
{
	if (obj->type == type_sphere)
		return (obj_sphere_surface_normal(&obj->as.sphere, point));
	else if (obj->type == type_plane)
		return (obj_plane_surface_normal(&obj->as.plane, point));
	else if (obj->type == type_cylinder)
		return (obj_cylinder_surface_normal(&obj->as.cylinder, point));
	return ((t_real3)(0, 0, 0));
}

t_real3			obj_sphere_surface_normal(t_sphere *sphere, t_real3 point)
{
	t_real3		normal;

	normal = point - sphere->pos;
	normal = normalize(normal);
	return (normal);
}

t_real3			obj_cylinder_surface_normal(t_cylinder *cylinder, t_real3 point)
{
	t_real		h;
	t_real		d;
	t_real3		normal;

	h = dot(cylinder->pos - point, cylinder->pos - point);
	d = sqrt(h - cylinder->radius * cylinder->radius);
	h = dot(point - cylinder->pos, cylinder->normal);
	if (fabs(h) < 1e-3)
		d = 0;
	else if (h > 0)
		d = -d;
	normal = cylinder->normal * d + (point - cylinder->pos);
	normal = normalize(normal);
	return (normal);
}

t_real3			obj_plane_surface_normal(t_plane *plane, t_real3 point)
{
	return (plane->normal);
}

#endif
