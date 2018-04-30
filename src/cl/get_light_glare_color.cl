#ifndef GET_LIGHT_GLARE_COLOR_CL
# define GET_LIGHT_GLARE_COLOR_CL

# include "host.h"

float3		get_light_glare_color(
		global t_config *config,
		constant t_obj *objs, uint objs_size,
		constant t_light *lights, uint lights_size,
		constant t_material *mats, uint mats_size,
		t_ray eye_ray);

float3		get_light_glare_color(
		global t_config *config,
		constant t_obj *objs, uint objs_size,
		constant t_light *lights, uint lights_size,
		constant t_material *mats, uint mats_size,
		t_ray eye_ray)
{
	float3		color;
	float3		light_color;
	t_ray		light_ray;
	t_real		light_dist;
	t_real		edl;
	t_real		t;
	t_obj_id	obj_id;
	int			i;

	color = (float3)(0, 0, 0);
	light_ray.origin = eye_ray.origin;
	i = -1;
	while (++i < (int)lights_size)
	{
		if (lights[i].glare < config->color_epsilon)
			continue ;
		light_ray.dir = light_get_dir_options(config, lights[i], light_ray.origin, &light_color, &light_dist, 1, 0);
		edl = dot(eye_ray.dir, light_ray.dir);
		if (edl < config->color_epsilon)
			continue ;
		if ((obj_id = ray_throw_get_first_hit_obj(config, &light_ray, objs, objs_size, &t)) < 0 || light_dist < t
				|| mats[objs[obj_id].material_id].ignores_light)
			color += lights[i].glare * light_color * edl;
	}
	return (color);
}

#endif
