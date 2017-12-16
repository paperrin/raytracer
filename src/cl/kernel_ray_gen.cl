#include "shared.h"

kernel void			kernel_ray_gen(
		constant read_only t_camera *cam,
		constant read_only uint2 *screen_size,
		global write_only float3 *pos,
		global write_only float3 *dir)
{
	const int		id = get_global_id(0);

	pos[id] = cam->pos;
	dir[id] = (
		cam->dir
		+ ((float)(id % screen_size->x) / (screen_size->x / 2) - 1)
			* cam->right
		- ((float)(id / screen_size->x) / (screen_size->y / 2) - 1)
			* cam->up
	);
}
