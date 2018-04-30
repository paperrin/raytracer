#ifndef UTILS_CL
# define UTILS_CL

# include "host.h"

t_real2				get_current_plane_pos(
		global read_only t_config *config,
		constant read_only t_camera_data *cam);

int2				get_current_pxl_pos(global read_only t_config *config);
t_real2				get_current_sub_pxl_pos(global read_only t_config *config);
int					get_current_pxl_id(global read_only t_config *config);
float3				filter_anaglyph(global read_only t_config *config, int pxl_id, float3 color);

int					get_pixel_samples_count(global read_only t_config *config);
int					get_screen_pixels_count(global read_only t_config *config);
int					get_screen_samples_count(global read_only t_config *config);

int					get_current_pxl_id(global read_only t_config *config)
{
	const int		n_samples = config->samples_width * config->samples_width;
	int				pxl_id;

	pxl_id = get_global_id(0);
	if (n_samples > 1)
		pxl_id /= n_samples;
	return (pxl_id);
}

t_real2				get_current_plane_pos(
		global read_only t_config *config,
		constant read_only t_camera_data *cam)
{
	const t_real	screen_ratio = (t_real)config->screen_size.y / config->screen_size.x;
	t_real2			plane_size = (t_real2)(tan(cam->fov / 2) * 2, tan(cam->fov / 2) * 2);
	t_real2			pxl_pos;
	t_real2			plane_pos;

	pxl_pos = (t_real2)convert_float2(get_current_pxl_pos(config));
	if (cam->eye_offset > 0 && !cam->is_anaglyph)
	{
		if (pxl_pos.x >= config->screen_size.x / 2)
			pxl_pos.x = (int)pxl_pos.x % (config->screen_size.x / 2);
		plane_size /= 2;
	}
	pxl_pos += get_current_sub_pxl_pos(config);
	plane_pos = pxl_pos / (t_real2)convert_float2(config->screen_size) * plane_size - plane_size / 2;
	plane_pos.y *= screen_ratio;
	return (plane_pos);
}

int					get_screen_pixels_count(global read_only t_config *config)
{
	return (config->screen_size.x * config->screen_size.y);
}

int					get_pixel_samples_count(global read_only t_config *config)
{
	return (config->samples_width * config->samples_width);
}

int					get_screen_samples_count(global read_only t_config *config)
{
	return (get_screen_pixels_count(config) * get_pixel_samples_count(config));
}

int2				get_current_pxl_pos(global read_only t_config *config)
{
	const int		pxl_id = get_current_pxl_id(config) % get_screen_pixels_count(config);
	int2			pxl_pos;

	pxl_pos = (int2)(
		pxl_id % config->screen_size.x,
		pxl_id / config->screen_size.x
	);
	return (pxl_pos);
}

t_real2				get_current_sub_pxl_pos(global read_only t_config *config)
{
	const int		gid = get_global_id(0);
	const int		n_samples = config->samples_width * config->samples_width;
	int				sub_pxl_id;
	t_real2			sub_pxl_pos;

	sub_pxl_id = gid % n_samples;
	sub_pxl_pos = (t_real2)(
		(t_real)(sub_pxl_id % config->samples_width) / (t_real)config->samples_width,
		(t_real)(sub_pxl_id / config->samples_width) / (t_real)config->samples_width
	);
	return (sub_pxl_pos);
}

float3				filter_anaglyph(global read_only t_config *config, int pxl_id, float3 color)
{
	float3		new_color;
	int			is_right_eye;

	new_color = (float3)(1);
	is_right_eye = pxl_id > get_screen_pixels_count(config);
	new_color.r = dot(color, config->anaglyph_r[is_right_eye]);
	new_color.g = dot(color, config->anaglyph_g[is_right_eye]);
	new_color.b = dot(color, config->anaglyph_b[is_right_eye]);
	return (new_color);
}

#endif
