#include "shared.h"
#include "obj_ray_hit.cl"

kernel void			kernel_ray_trace(
		constant read_only t_obj *objs,
		constant read_only uint *objs_size,
		global read_only t_ray_state *ray_states,
		global read_write uint *n_hits,
		global read_only t_config *config)
{

	const int		gid = get_global_id(0);
	uint			new_id;
	t_real			t_nearest;
	t_obj_id		obj_id_nearest;
	t_ray			ray;
	t_ray_state		state;

	state = ray_states[gid];
	ray = state.ray;
	obj_id_nearest = ray_throw_get_first_hit_obj(&ray, objs, *objs_size, &t_nearest);
	state.t = (t_nearest < 200000) ? t_nearest : -1;
	state.obj_id = obj_id_nearest;
	barrier(CLK_GLOBAL_MEM_FENCE);
	if (obj_id_nearest > -1 )
		new_id = atomic_inc(n_hits);
	if (config->ray_compaction && obj_id_nearest > -1)
		ray_states[new_id] = state;
	else
		ray_states[gid] = state;
}
