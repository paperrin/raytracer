#include "host.h"

t_real3				light_get_dir(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);
t_real3				light_get_dir_options(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist, int no_intensity, int no_dispersion);
t_real3				light_point_get_dir(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);
t_real3				light_dir_get_dir(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);
t_real3				light_spot_get_dir(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);
t_real3				light_point_get_dir_options(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist, int no_intensity, int no_dispersion);
t_real3				light_dir_get_dir_options(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist, int no_intensity, int no_dispersion);
t_real3				light_spot_get_dir_options(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist, int no_intensity, int no_dispersion);

t_real3				light_get_dir(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist)
{
	return (light_get_dir_options(config, light, to_pos, color, dist, 0, 0));
}
t_real3				light_get_dir_options(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist, int no_intensity, int no_dispersion)
{
	*dist = -1;
	*color = (cl_float3)(0, 0, 0);
	if (light.type == e_light_type_point)
		return (light_point_get_dir_options(config, light, to_pos, color, dist, no_intensity, no_dispersion));
	else if (light.type == e_light_type_dir)
		return (light_dir_get_dir_options(config, light, to_pos, color, dist, no_intensity, no_dispersion));
	else if (light.type == e_light_type_spot)
		return (light_spot_get_dir_options(config, light, to_pos, color, dist, no_intensity, no_dispersion));
	return ((t_real3)(0, 0, 0));
}

t_real3				light_point_get_dir_options(const global t_config *config, t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist, int no_intensity, int no_dispersion)
{
	t_real3		dir;
	t_real		r2;

	dir = light.as.point.pos - to_pos;
	r2 = dot(dir, dir);
	*dist = sqrt(r2);
	dir /= *dist;
	*color = light.color;
	if (!no_intensity)
		*color *= light.intensity;
	if (!no_dispersion && light.dispersion > config->color_epsilon)
		*color /= (float)(light.dispersion * 4 * M_PI_F * (float)r2);
	return (dir);
}

t_real3				light_dir_get_dir_options(const global t_config *config, t_light light, t_real3 to_pos,
	cl_float3 *color, t_real *dist, int no_intensity, int no_dispersion)
{
	*dist = REAL_MAX;
	*color = light.color;
	if (!no_intensity)
		*color *= light.intensity;
	return (-light.as.dir.dir);
}

t_real3				light_spot_get_dir_options(const global t_config *config, t_light light, t_real3 to_pos,
	cl_float3 *color, t_real *dist, int no_intensity, int no_dispersion)
{
	t_real3			dir;
	t_real			radial_dist;
	t_real			r2;
	t_real			outter_intensity;

	dir = light.as.spot.pos - to_pos;
	r2 = dot(dir, dir);
	*dist = sqrt(r2);
	dir /= *dist;
	radial_dist = fabs(dot(-dir - light.as.spot.dir, -dir - light.as.spot.dir)) * 2;
	*color = (cl_float3)(0, 0, 0);
	if (radial_dist < light.as.spot.field_aperture)
	{
		if (radial_dist < light.as.spot.beam_aperture * (1 - light.as.spot.beam_gradient))
			*color = light.color;
		else if (radial_dist < light.as.spot.beam_aperture)
		{
			*color = light.color * light.as.spot.field_intensity
				+ (1 - light.as.spot.field_intensity)
				* (1 - ((radial_dist - light.as.spot.beam_aperture * (1 - light.as.spot.beam_gradient))
					/ (light.as.spot.beam_aperture - light.as.spot.beam_aperture * (1 - light.as.spot.beam_gradient))));
		}
		else
		{
			outter_intensity = (1 - ((radial_dist - light.as.spot.beam_aperture)
					/ (light.as.spot.field_aperture - light.as.spot.beam_aperture)));
			*color = light.color * light.as.spot.field_intensity * outter_intensity * outter_intensity;
		}
		if (!no_intensity)
			*color *= light.intensity;
	}
	if (!no_dispersion && light.dispersion > config->color_epsilon)
		*color /= (float)(light.dispersion * 4 * M_PI_F * (float)r2);
	return (dir);
}
