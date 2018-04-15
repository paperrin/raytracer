#ifndef OBJ_SURFACE_UV_MAP_CL
# define OBJ_SURFACE_UV_MAP_CL

#include "shared.h"
#include "host.h"
#include "obj_surface_normal.cl"

t_real2			obj_surface_uv_map(t_obj *obj, t_real3 point);
t_real2			obj_sphere_surface_uv_map(t_sphere *sphere, t_real3 point);
t_real2			obj_plane_surface_uv_map(t_plane *plane, t_real3 point);
t_real2			obj_aligned_cube_surface_uv_map(t_aligned_cube *aligned_cube, t_real3 point);

t_real2			obj_surface_uv_map(t_obj *obj, t_real3 point)
{
	t_real2		uv;

	if (obj->type == e_type_sphere)
		uv = obj_sphere_surface_uv_map(&obj->as.sphere, point);
	else if (obj->type == e_type_plane)
		uv = obj_plane_surface_uv_map(&obj->as.plane, point);
	else if (obj->type == e_type_aligned_cube)
		uv = obj_aligned_cube_surface_uv_map(&obj->as.aligned_cube, point);
	else
		return ((t_real2)(0, 0));
	return (uv);
}

t_real2			obj_sphere_surface_uv_map(t_sphere *sphere, t_real3 point)
{
	t_real3		surface_normal;
	t_real		phi;
	t_real2		uv;
	t_real		theta;

	surface_normal = normalize(point - sphere->pos);
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
	return (uv);
}

t_real2		obj_aligned_cube_surface_uv_map(t_aligned_cube *aligned_cube, t_real3 point)
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
	pdir.v = (point - aligned_cube->pos) / aligned_cube->size;
	pdir.v.xyz = pdir.v.xzy;
	vec.v = (aligned_cube->pos + aligned_cube->size / (t_real)2 - point) / aligned_cube->size;
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
