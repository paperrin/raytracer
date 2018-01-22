#ifndef OBJ_SURFACE_UV_MAP_CL
# define OBJ_SURFACE_UV_MAP_CL

#include "shared.h"
#include "obj_surface_normal.cl"

t_real2			obj_surface_uv_map(t_obj *obj, t_real3 point);
t_real2			obj_sphere_surface_uv_map(t_sphere *sphere, t_real3 point);

t_real2			obj_surface_uv_map(t_obj *obj, t_real3 point)
{
	if (obj->type == type_sphere)
		return (obj_sphere_surface_uv_map(&obj->as.sphere, point));
	return ((t_real2)(0, 0));
}

t_real2			obj_sphere_surface_uv_map(t_sphere *sphere, t_real3 point)
{
	t_real3		surface_normal;
	t_real		phi;
	t_real2		uv;
	t_real		theta;

	surface_normal = obj_sphere_surface_normal(sphere, point);
	phi = acos(-dot(sphere->up, surface_normal));
	uv.y = 1 - (phi / M_PI);
	theta = acos(dot(surface_normal, sphere->front) / sin(phi)) / (2 * M_PI);
	if (dot(cross(sphere->front, sphere->up), surface_normal) > 0)
		uv.x = theta;
	else
		uv.x = 1 - theta;
	return (uv);
}

#endif
