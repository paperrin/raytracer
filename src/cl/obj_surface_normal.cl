#ifndef OBJ_SURFACE_NORMAL_CL
# define OBJ_SURFACE_NORMAL_CL

#include "shared.h"

t_real3			obj_surface_normal(t_obj *obj, t_real3 point);
t_real3			obj_sphere_surface_normal(t_sphere *sphere, t_real3 point);
t_real3			obj_plane_surface_normal(t_plane *plane, t_real3 point);

t_real3			obj_surface_normal(t_obj *obj, t_real3 point)
{
	if (obj->type == type_sphere)
		return (obj_sphere_surface_normal(&obj->as.sphere, point));
	else if (obj->type == type_plane)
		return (obj_plane_surface_normal(&obj->as.plane, point));
	return ((t_real3)(0, 0, 0));
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
