#include "shared.h"
#include "obj_ray_hit.cl"

kernel void			kernel_ray_trace(
		constant read_only t_obj *objs,
		global read_only uint *objs_size,
		global read_write t_ray_state *ray_states,
		global read_only t_config *config,
		global read_write uint *ray_hits,
		volatile global read_write int *n_hits)
{

	const int		gid = get_global_id(0);
	t_real			t_nearest;
	t_obj_id		obj_id_nearest;
	t_ray_state		state;

	state = ray_states[gid];
	state.obj_id = -1;
	state.t = -1;
	ray_hits[gid] = 0;
	if (state.importance > 1e-4)
	{
		obj_id_nearest = ray_throw_get_first_hit_obj(&state.ray, objs, *objs_size, &t_nearest);
		if (t_nearest < 200000 - 1)
		{
			state.t = t_nearest;
			state.obj_id = obj_id_nearest;
			if (state.obj_id > -1)
			{
				ray_hits[gid] = 1;
				atomic_inc(n_hits);
			}
		}
	}
	ray_states[gid] = state;
}
