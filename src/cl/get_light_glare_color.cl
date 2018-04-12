#ifndef GET_LIGHT_GLARE_COLOR_CL
# define GL_LIGHT_GLARE_COLOR_CL

# include "shared.h"

float3		get_light_glare_color(
		global t_config *config,
		constant t_obj *objs, uint objs_size,
		constant t_light *lights, uint lights_size,
		t_ray eye_ray);

float3		get_light_glare_color(
		global t_config *config,
		constant t_obj *objs, uint objs_size,
		constant t_light *lights, uint lights_size,
		t_ray eye_ray)
{
	float3		color;
	float3		light_color;
	t_ray		light_ray;
	t_real		light_dist;
	t_real		edl;
	t_real		t;
	int			i;

	color = (float3)(0, 0, 0);
	light_ray.origin = eye_ray.origin;
	i = -1;
	while (++i < lights_size)
	{
		if (lights[i].glare < config->color_epsilon)
			continue ;
		light_ray.dir = light_get_dir(config, lights[i], light_ray.origin, &light_color, &light_dist);
		edl = dot(eye_ray.dir, light_ray.dir);
		if (edl < config->color_epsilon)
			continue ;
		if (ray_throw_get_first_hit_obj(config, &light_ray, objs, objs_size, &t) < 0 || light_dist < t)
			color += lights[i].glare * light_color * edl;
	}
	return (color);
}

#endif
