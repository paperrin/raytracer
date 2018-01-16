#include "shared.h"

t_real3			obj_surface_normal(constant t_obj *obj, t_real3 point);
t_real3			obj_sphere_surface_normal(constant t_sphere *sphere, t_real3 point);

t_real3			obj_surface_normal(constant t_obj *obj, t_real3 point)
{
	if (obj->type == type_sphere)
		return (obj_sphere_surface_normal(&obj->as.sphere, point));
	return ((t_real3)(0, 0, 0));
}

t_real3			obj_sphere_surface_normal(constant t_sphere *sphere, t_real3 point)
{
	t_real3		normal;

	normal = point - sphere->pos;
	normal = normalize(normal);
	return (normal);
}