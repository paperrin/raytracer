#include "shared.h"

t_real3			obj_surface_normal(t_obj *obj, t_real3 point);
t_real3			obj_sphere_surface_normal(t_sphere *sphere, t_real3 point);
t_real3			obj_cone_surface_normal(t_cone *cone, t_real3 point);

t_real3			obj_surface_normal(t_obj *obj, t_real3 point)
{
	if (obj->type == type_sphere)
		return (obj_sphere_surface_normal(&obj->as.sphere, point));
	else if (obj->type == type_cone)
		return (obj_cone_surface_normal(&obj->as.cone, point));
	return ((t_real3)(0, 0, 0));
}

t_real3			obj_sphere_surface_normal(t_sphere *sphere, t_real3 point)
{
	t_real3		normal;

	normal = point - sphere->pos;
	normal = normalize(normal);
	return (normal);
}

t_real3			obj_cone_surface_normal(t_cone *cone, t_real3 point)
{
	t_real3		normal;
	t_real		h;
	t_real		y;
	t_real3		c;

	normal = point - cone->pos;
	h = sqrt(dot(normal, normal));
	y = sqrt(h * h - dot(cone->radius, cone->radius));
	c = cone->up * y + cone->pos;
	normal = point - c;
	normal = normalize(normal);
	return (normal);
}
