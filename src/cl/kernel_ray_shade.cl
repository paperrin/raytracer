#include "shared.h"
#include "obj_ray_hit.cl"
#include "obj_surface_normal.cl"

kernel void			kernel_ray_shade(
		constant read_only t_obj *objs,
		constant read_only uint *objs_size,
		global read_only t_ray_state *ray_states,
		global read_only uint *n_hits,
		global write_only t_real *pixels)
{
	const int		gid = get_global_id(0);
	t_real3			hit_pos;
	t_real3			normal;

	hit_pos = ray_states[gid].ray.origin + ray_states[gid].t * ray_states[gid].ray.dir;
	normal = obj_surface_normal(&objs[ray_states[gid].obj_id], hit_pos);
	//* // normal map
	pixels[ray_states[gid].pxl_id * 4 + 0] = (normal.x + 1) / 2;
	pixels[ray_states[gid].pxl_id * 4 + 1] = 1 - (normal.y + 1) / 2;
	pixels[ray_states[gid].pxl_id * 4 + 2] = normal.z * -1;
	pixels[ray_states[gid].pxl_id * 4 + 3] = 1;
	//*/
	/* // height map
	pixels[ray_states[gid].pxl_id * 4 + 0] = normal.z * -1;
	pixels[ray_states[gid].pxl_id * 4 + 1] = normal.z * -1;
	pixels[ray_states[gid].pxl_id * 4 + 2] = normal.z * -1;
	pixels[ray_states[gid].pxl_id * 4 + 3] = 1;
	//*/
	/* // All red
	pixels[ray_states[gid].pxl_id * 4 + 0] = 1;
	pixels[ray_states[gid].pxl_id * 4 + 1] = 0;
	pixels[ray_states[gid].pxl_id * 4 + 2] = 0;
	pixels[ray_states[gid].pxl_id * 4 + 3] = 1;
	//*/
}

/*
color = Co * Ca;
if (!inShadow)
{
	color = MIN_MAX(0, color + Co * Cl * Li, 1) * Fabs + Crfl * Frfl + Crfr * Frfr;
}

color = get_shaded_color();
importance *= absFactor;

*/
