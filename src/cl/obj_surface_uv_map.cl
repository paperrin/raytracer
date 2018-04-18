#ifndef OBJ_SURFACE_UV_MAP_CL
# define OBJ_SURFACE_UV_MAP_CL

#include "shared.h"
#include "host.h"
#include "obj_surface_normal.cl"

t_real2			obj_surface_uv_map(t_obj const *const obj, t_real3 point);
t_real2			obj_sphere_surface_uv_map(t_obj const *const obj, t_real3 point);
t_real2			obj_plane_surface_uv_map(t_obj const *const obj, t_real3 point);
t_real2			obj_aligned_cube_surface_uv_map(t_obj const *const obj, t_real3 point);
t_real2			obj_cone_surface_uv_map(t_obj const *const obj, t_real3 point);
t_real2			obj_cylinder_surface_uv_map(t_obj const *const obj, t_real3 point);

t_real2			obj_surface_uv_map(t_obj const *const obj, t_real3 point)
{
	t_real2		uv;

	if (obj->type == e_type_sphere)
		uv = obj_sphere_surface_uv_map(obj, point);
	else if (obj->type == e_type_plane)
		uv = obj_plane_surface_uv_map(obj, point);
	else if (obj->type == e_type_cylinder)
		return (obj_cylinder_surface_uv_map(obj, point));
	else if (obj->type == e_type_cone)
		return (obj_cone_surface_uv_map(obj, point));
	else if (obj->type == e_type_aligned_cube)
		uv = obj_aligned_cube_surface_uv_map(obj, point);
	else
		return ((t_real2)(0, 0));
	return (uv);
}

t_real2			obj_sphere_surface_uv_map(t_obj const *const obj, t_real3 point)
{
	t_real3		surface_normal;
	t_real		phi;
	t_real2		uv;
	t_real		theta;

	surface_normal = normalize(point - obj->pos);
	phi = acos(-dot(obj->up, surface_normal));
	uv.y = 1.f - (phi / M_PI_F);
	theta = acos(clamp(dot(obj->normal, surface_normal) / sin(phi), -1.f, 1.f)) / (2.f * M_PI_F);
	if (dot(cross(obj->normal, obj->up), surface_normal) <= 0)
		uv.x = 1 - theta;
	else
		uv.x = theta;
	return (uv);
}

t_real2			obj_plane_surface_uv_map(t_obj const *const obj, t_real3 point)
{
	t_real3		right;
	t_real2		uv;

	right = cross(obj->up, obj->normal);
	point -= obj->pos;
	uv.x = dot(obj->normal, point);
	uv.y = dot(right, point);
	return (uv);
}

t_real2			obj_cylinder_surface_uv_map(t_obj const *const obj, t_real3 point)
{
	t_real3		surface_normal;
	t_real2		uv;
	t_real		theta;
	t_real		phi;
	t_real		h;
	t_real		d;

	h = dot(obj->pos - point, obj->pos - point);
	d = sqrt(h - obj->as.cylinder.radius * obj->as.cylinder.radius);

	uv.y = d;

	surface_normal = obj_cylinder_surface_normal(obj, point);
	phi = acos(-dot(obj->normal, surface_normal));
	theta = acos(dot(obj->normal, surface_normal)) / ((t_real)2 * M_PI_F);
	if (dot(cross(obj->normal, obj->up), surface_normal) <= 0)
		uv.x = 1 - theta;
	else
		uv.x = theta;
	return (uv);
}

t_real2			obj_cone_surface_uv_map(t_obj const *const obj, t_real3 point)
{
	t_real2		uv;
	t_real3		center_to_pos;
	t_real		side;

	side = 1;
	if(dot(obj->up, point - obj->pos) < 0)
		side = -side;
	uv.y = cos(obj->as.cone.angle) * length(point - obj->pos) * side;
	center_to_pos = obj_cone_surface_normal(obj, point);
	uv.x = acos(dot(center_to_pos, obj->normal)) / (M_PI_F * (t_real)2);
	if (dot(cross(obj->normal, obj->up), center_to_pos) <= 0)
		uv.x = (t_real)1 - uv.x;
	return (uv);
}

t_real2		obj_aligned_cube_surface_uv_map(t_obj const *const obj, t_real3 point)
{
	t_real2s	uv;
	t_real3s	pdir;
	t_real		max_val;
	int			i;
	int			j;
	int			side;
	t_real3s	vec;

	i = 0;
	j = 0;
	pdir.v = (point - obj->pos) / obj->as.aligned_cube.size;
	pdir.v.xyz = pdir.v.xzy;
	vec.v = (obj->pos + obj->as.aligned_cube.size / (t_real)2 - point) / obj->as.aligned_cube.size;
	vec.v.x = (t_real)1 - vec.v.x;
	vec.v.xyz = vec.v.xzy;
	max_val = max(max(fabs(pdir.v.x), fabs(pdir.v.y)), fabs(pdir.v.z));
	while (i <= 2)
	{
		if (max_val == fabs(pdir.s[i]))
			side = (pdir.s[i] < (t_real)0);
		else
		{
			uv.s[j] = vec.s[i];
			j++;
		}
		i++;
	}
	if (!side)
		uv.v.x = (t_real)1 - uv.v.x;
	return (uv.v);
}

#endif
