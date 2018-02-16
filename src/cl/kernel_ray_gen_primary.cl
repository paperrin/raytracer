#include "shared.h"

kernel void			kernel_ray_gen_primary(
		constant read_only t_config *config,
		constant read_only t_camera_data *cam,
		global write_only t_ray_state *ray_states)
{
	const int		gid = get_global_id(0);

	ray_states[gid].ray.origin = cam->pos;
	ray_states[gid].ray.dir = normalize(
		cam->dir
		+ ((t_real)(gid % config->screen_size.x) / (config->screen_size.x / 2) - 1)
			* cam->right
		- ((t_real)(gid / config->screen_size.x) / (config->screen_size.y / 2) - 1)
			* ((t_real)config->screen_size.y / config->screen_size.x)
			* cam->up
	);
	ray_states[gid].importance = 1;
	ray_states[gid].pxl_id = gid;
}
