#include "shared.h"
#include "obj_ray_hit.cl"
#include "obj_surface_normal.cl"

float				real_min_max(t_real min, t_real value, t_real max);
t_real3				shade(t_obj obj, t_real3 hit_pos,
		constant t_obj *objs, cl_uint objs_size,
		constant t_material *mats, cl_uint mats_size,
		constant t_light *lights, cl_uint lights_size);
t_real3				light_get_dir(t_light light, t_real3 to_pos,
		t_real3 *light_color);

kernel void			kernel_ray_shade(
		constant read_only t_obj *objs,
		constant read_only uint *objs_size,
		constant read_only t_material *mats,
		constant read_only uint *mats_size,
		constant read_only t_light *lights,
		constant read_only uint *lights_size,
		global read_only t_ray_state *ray_states,
		global write_only t_real *pixels)
{
	const int				gid = get_global_id(0);
	t_real3					hit_pos;
	t_real3					normal;
	t_real3					color;
	t_obj					obj;

	obj = objs[ray_states[gid].obj_id];
	hit_pos = ray_states[gid].ray.origin + ray_states[gid].t * ray_states[gid].ray.dir;
	normal = obj_surface_normal(&obj, hit_pos);
	hit_pos += normal * (float)1e-5;
	color = shade(obj, hit_pos,
			objs, *objs_size,
			mats, *mats_size,
			lights, *lights_size);
	pixels[ray_states[gid].pxl_id * 4 + 0] = color.r;
	pixels[ray_states[gid].pxl_id * 4 + 1] = color.g;
	pixels[ray_states[gid].pxl_id * 4 + 2] = color.b;
	pixels[ray_states[gid].pxl_id * 4 + 3] = 1;
}

float				real_min_max(t_real min, t_real value, t_real max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

t_real3				light_get_dir(t_light light, t_real3 to_pos,
		t_real3 *light_color)
{
	t_real3		dir;

	*light_color = (t_real3)(0, 0, 0);
	dir = (t_real3)(0, 0, 0);
	if (light.type == light_type_point)
	{
		dir = normalize(light.as.point.pos - to_pos);
		*light_color = light.color * light.intensity;
	}
	return (dir);
}

t_real3				shade(t_obj obj, t_real3 hit_pos,
		constant t_obj *objs, cl_uint objs_size,
		constant t_material *mats, cl_uint mats_size,
		constant t_light *lights, cl_uint lights_size)
{
	t_real3			surface_normal;
	t_real			surface_diffuse;
	t_ray			light_ray;
	t_real3			light_color;
	cl_float		t;
	char			in_shadow;
	t_real3			color;
	int				i;

	surface_normal = obj_surface_normal(&obj, hit_pos);
	light_ray.origin = hit_pos;
	color = (t_real3)(0, 0, 0);
	color = mats[obj.material_id].color * (t_real3)(0.0, 0.0, 0.05);
	i = -1;
	while (++i < lights_size)
	{
		light_ray.dir = light_get_dir(lights[i], hit_pos, &light_color);
		if (!(ray_throw_get_any_hit_obj(&light_ray, objs, objs_size, &t) > -1 && t >= 0))
		{
			color += mats[obj.material_id].color * light_color
				* dot(light_ray.dir, surface_normal);
		}
	}
	color.r = real_min_max(0, color.r, 1);
	color.g = real_min_max(0, color.g, 1);
	color.b = real_min_max(0, color.b, 1);
	return (color);
}
