#include "host.h"
#include "utils.cl"

kernel void			kernel_ray_gen_primary(
		global read_only t_config *config,
		constant read_only t_camera_data *cam,
		global write_only t_ray_state *ray_states)
{
	const int		gid = get_global_id(0);
	ulong			pxl_id = get_current_pxl_id(config);
	t_real2			plane_pos = get_current_plane_pos(config, cam);
	t_real3			eye_half_offset = cam->eye_offset / 2 * cam->right;
	int				n_screen_pixels = get_screen_pixels_count(config);
	int				is_right_eye;
	t_real3			ray_origin;

	ray_states[gid].ray.dir = normalize(
		cam->dir
		+ cam->right * plane_pos.x
		- cam->up * plane_pos.y
	);
	ray_origin = cam->pos;
	if (cam->eye_offset > FLT_MIN)
	{
		if (cam->is_anaglyph)
		{
			is_right_eye = get_current_pxl_id(config) > n_screen_pixels;
			if (!is_right_eye)
				eye_half_offset *= -1;
		}
		else
		{
			is_right_eye = get_current_pxl_pos(config).x < (int)config->screen_size.x / 2;
			if (!is_right_eye)
				eye_half_offset *= -1;
		}
		ray_origin -= eye_half_offset;
	}

	ray_states[gid].ray.origin = ray_origin;
	ray_states[gid].color_factor = (float3)(1);
	ray_states[gid].importance = 1.f;
	ray_states[gid].pxl_id = pxl_id;
}
