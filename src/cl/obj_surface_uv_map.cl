#ifndef OBJ_SURFACE_UV_MAP_CL
# define OBJ_SURFACE_UV_MAP_CL

#include "shared.h"
#include "obj_surface_normal.cl"

t_real2			obj_surface_uv_map(t_obj *obj, t_real3 point);
t_real2			obj_sphere_surface_uv_map(t_sphere *sphere, t_real3 point);
t_real2			obj_plane_surface_uv_map(t_plane *plane, t_real3 point);
t_real2			obj_cylinder_surface_uv_map(t_cylinder *cylinder, t_real3 point);

t_real2			obj_surface_uv_map(t_obj *obj, t_real3 point)
{
	if (obj->type == type_sphere)
		return (obj_sphere_surface_uv_map(&obj->as.sphere, point));
	else if (obj->type == type_plane)
		return (obj_plane_surface_uv_map(&obj->as.plane, point));
	else if (obj->type == type_cylinder)
		return (obj_cylinder_surface_uv_map(&obj->as.plane, point));
	return ((t_real2)(0, 0));
}

t_real2			obj_sphere_surface_uv_map(t_sphere *sphere, t_real3 point)
{
	t_real3		surface_normal;
	t_real		phi;
	t_real2		uv;
	t_real		theta;

	surface_normal = normalize(obj_sphere_surface_normal(sphere, point));
	phi = acos(-dot(sphere->up, surface_normal));
	uv.y = 1.f - (phi / M_PI_F);
	theta = acos(clamp(dot(sphere->front, surface_normal) / sin(phi), -1.f, 1.f)) / (2.f * M_PI_F);
	if (dot(cross(sphere->front, sphere->up), surface_normal) <= 0)
		uv.x = 1 - theta;
	else
		uv.x = theta;
	return (uv);
}

t_real2			obj_plane_surface_uv_map(t_plane *plane, t_real3 point)
{
	t_real3		right;
	t_real2		uv;

	right = cross(plane->up, plane->normal);
	point -= plane->pos;
	uv.x = dot(plane->up, point);
	uv.y = dot(right, point);
	uv -= (t_real2)(floor(uv.x), floor(uv.y));
	return (uv);
}

t_real2			obj_cylinder_surface_uv_map(t_cylinder *cylinder, t_real3 point)
{
	t_real3		surface_normal;
	t_real2		uv;
	t_real		phi;
	t_real		h;
	t_real		d;

	surface_normal = normalize(obj_cylinder_surface_normal(cylinder, point));
	phi = acos(-dot(cylinder->up, surface_normal));
	uv.y = 1.f - (phi / M_PI_F);
	h = dot(cylinder->pos - point, cylinder->pos - point);
	d = sqrt(h - cylinder->radius * cylinder->radius);
	uv.x = d;
	uv -= (t_real2)(floor(uv.x), floor(uv.y));
	return (uv);

//	t_real3		surface_normal;
//	t_real2		uv;
//
//	surface_normal = normalize(obj_cylinder_surface_normal(cylinder, point));
//	uv.x = atan2(surface_normal.x, surface_normal.z) / (2 * M_PI_F) + 1.f;
//	uv.y = surface_normal.y * 1.f + 1.f;
//	return (uv);
}

#endif
