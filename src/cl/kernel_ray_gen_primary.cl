#include "shared.h"

kernel void			kernel_ray_gen_primary(
		global read_only t_config *config,
		constant read_only t_camera_data *cam,
		global write_only t_ray_state *ray_states)
{
	const int		gid = get_global_id(0);
	uint			n_samples = config->samples_width * config->samples_width;
	ulong			pxl_id = (config->samples_width == 1) ? gid : gid / n_samples;
	uint2			pos = (uint2)(
			gid % config->samples_width,
			gid % n_samples / config->samples_width);

	ray_states[gid].ray.origin = cam->pos;
	ray_states[gid].ray.dir = normalize(
		cam->dir
		+ ((t_real)(pxl_id % config->screen_size.x * config->samples_width + pos.x) / (config->screen_size.x * config->samples_width / 2) - 1)
			* cam->right
		- ((t_real)(pxl_id / config->screen_size.x * config->samples_width + pos.y) / (config->screen_size.y * config->samples_width / 2) - 1)
			* ((t_real)config->screen_size.y / config->screen_size.x)
			* cam->up
	);
	ray_states[gid].color_factor = (float3)(1);
	ray_states[gid].importance = 1.f;
	ray_states[gid].pxl_id = pxl_id;
}
