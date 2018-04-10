#include "shared.h"

t_real3				light_get_dir(t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);
t_real3				light_point_get_dir(t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);
t_real3				light_dir_get_dir(t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);
t_real3				light_spot_get_dir(t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);

t_real3				light_get_dir(t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist)
{
	*dist = -1;
	*color = (cl_float3)(0, 0, 0);
	if (light.type == light_type_point)
		return (light_point_get_dir(light, to_pos, color, dist));
	else if (light.type == light_type_dir)
		return (light_dir_get_dir(light, to_pos, color, dist));
	else if (light.type == light_type_spot)
		return (light_spot_get_dir(light, to_pos, color, dist));
	return ((t_real3)(0, 0, 0));
}

t_real3				light_point_get_dir(t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist)
{
	t_real3		dir;
	t_real		r2;

	dir = light.as.point.pos - to_pos;
	r2 = dot(dir, dir);
	*dist = sqrt(r2);
	dir /= *dist;
	*color = light.color * light.intensity / (float)(4 * M_PI_F * (float)r2);
	return (dir);
}

t_real3				light_dir_get_dir(t_light light, t_real3 to_pos,
	cl_float3 *color, t_real *dist)
{
	*dist = REAL_MAX;
	*color = light.color * light.intensity;
	return (-light.as.dir.dir);
}

t_real3				light_spot_get_dir(t_light light, t_real3 to_pos,
	cl_float3 *color, t_real *dist)
{
	const t_real	middle_gradient = 1;
	const t_real	field_intensity = 0.05;
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
		*color = light.color;
		if (radial_dist < light.as.spot.beam_aperture * (1 - middle_gradient))
			*color *= light.intensity;
		else if (radial_dist < light.as.spot.beam_aperture)
		{
			*color *= field_intensity * light.intensity
				+ light.intensity * (1 - field_intensity)
				* (1 - ((radial_dist - light.as.spot.beam_aperture * (1 - middle_gradient))
					/ (light.as.spot.beam_aperture - light.as.spot.beam_aperture * (1 - middle_gradient))));		
		}
		else
		{
			outter_intensity = (1 - ((radial_dist - light.as.spot.beam_aperture)
					/ (light.as.spot.field_aperture - light.as.spot.beam_aperture)));
			*color *= field_intensity * light.intensity
				* outter_intensity * outter_intensity;
		}	
	}
	return (dir);
}
