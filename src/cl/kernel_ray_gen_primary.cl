#include "shared.h"

kernel void			kernel_ray_gen_primary(
		global read_only uint2 *screen_size,
		global read_only t_camera *cam,
		global write_only t_ray_state *ray_states)
{
	const int		id = get_global_id(0);

	ray_states[id].ray.origin = cam->pos;
	ray_states[id].ray.dir = normalize(
		cam->dir
		+ ((t_real)(id % screen_size->x) / (screen_size->x / 2) - 1)
			* cam->right
		- ((t_real)(id / screen_size->x) / (screen_size->y / 2) - 1)
			* ((t_real)screen_size->y / screen_size->x)
			* cam->up
	);
}
