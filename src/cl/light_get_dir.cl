#include "shared.h"

t_real3				light_get_dir(t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);
t_real3				light_point_get_dir(t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist);

t_real3				light_get_dir(t_light light, t_real3 to_pos,
		cl_float3 *color, t_real *dist)
{
	*dist = -1;
	*color = (cl_float3)(0, 0, 0);
	if (light.type == light_type_point)
		return (light_point_get_dir(light, to_pos, color, dist));
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
	*color = light.color * light.intensity / (float)(4 * M_PI * (float)r2);
	return (dir);
}
