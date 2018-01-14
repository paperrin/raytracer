#include "shared.h"
#include "obj_ray_hit.cl"
#include "obj_surface_normal.cl"

kernel void			kernel_compute_texels(
		constant read_only t_obj *objs,
		constant read_only uint *objs_size,
		global read_only t_ray_state *ray_states,
		global read_only t_hit *hits,
		global read_only uint *n_hits,
		global write_only t_texel *texels)
{
	const int		gid = get_global_id(0);
	t_real3			hit_pos;
	t_real3			normal;
	t_ray			ray;

	ray = ray_states[hits[gid].px_id].ray;
	hit_pos = ray.origin + hits[gid].t * ray.dir;
	normal = obj_surface_normal(&objs[hits[gid].obj_id], hit_pos);
	//* // normal map
	texels[gid].r = (normal.x + 1) / 2;
	texels[gid].g = 1 - (normal.y + 1) / 2;
	texels[gid].b = normal.z * -1;
	//*/
	/* // height map
	texels[gid].r = normal.z * -1;
	texels[gid].g = normal.z * -1;
	texels[gid].b = normal.z * -1;
	//*/
	texels[gid].factor = 1;
	texels[gid].px_id = hits[gid].px_id;
	texels[gid].obj_id = hits[gid].obj_id;
}

/*
color = Co * Ca;
if (!inShadow)
{
	color = MIN_MAX(0, color + Co * Cl * Li, 1) * Fabs + Crfl * Frfl + Crfr * Frfr;
}

*/
