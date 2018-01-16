#include "shared.h"
#include "obj_ray_hit.cl"

kernel void			kernel_ray_trace(
		constant read_only t_obj *objs,
		constant read_only uint *objs_size,
		global read_only t_ray_state *ray_states,
		global read_write uint *n_hits)
{
	const int		gid = get_global_id(0);
	uint			new_id;
	t_obj_id		i;
	t_real			t;
	t_real			t_nearest;
	t_obj_id		obj_id_nearest;

	i = -1;
	t_nearest = 200000;
	obj_id_nearest = -1;
	while (++i < (t_obj_id)*objs_size)
	{
		if ((t = obj_ray_hit(&objs[i], &ray_states[gid].ray)) >= 0 && t < t_nearest)
		{
			t_nearest = t;
			obj_id_nearest = i;
		}
	}
	if (obj_id_nearest > -1)
	{
		new_id = atomic_add(n_hits, 1);
		ray_states[new_id].ray = ray_states[gid].ray;
		ray_states[new_id].pxl_id = gid;
		ray_states[new_id].t = (t_nearest < 200000) ? t_nearest : -1;
		ray_states[new_id].obj_id = obj_id_nearest;
	}
}
