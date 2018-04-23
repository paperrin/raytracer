#include "shared.h"
#include "utils.cl"

kernel void			kernel_ray_gen_primary(
		global read_only t_config *config,
		constant read_only t_camera_data *cam,
		global write_only t_ray_state *ray_states)
{
	const int		gid = get_global_id(0);
	const ulong		pxl_id = get_current_pxl_id(config);
	t_real2			plane_pos = get_current_plane_pos(config, cam);

	ray_states[gid].ray.dir = normalize(
		cam->dir
		+ cam->right * plane_pos.x
		- cam->up * plane_pos.y
	);
	ray_states[gid].ray.origin = cam->pos;
	ray_states[gid].color_factor = (float3)(1);
	ray_states[gid].importance = 1.f;
	ray_states[gid].pxl_id = pxl_id;
}
