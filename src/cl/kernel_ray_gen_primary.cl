#include "shared.h"

kernel void			kernel_ray_gen_primary(
		constant read_only uint2 *screen_size,
		constant read_only t_camera_data *cam,
		global write_only t_ray_state *ray_states)
{
	const int		gid = get_global_id(0);

	ray_states[gid].ray.origin = cam->pos;
	ray_states[gid].ray.dir = normalize(
		cam->dir
		+ ((t_real)(gid % screen_size->x) / (screen_size->x / 2) - 1)
			* cam->right
		- ((t_real)(gid / screen_size->x) / (screen_size->y / 2) - 1)
			* ((t_real)screen_size->y / screen_size->x)
			* cam->up
	);
}
