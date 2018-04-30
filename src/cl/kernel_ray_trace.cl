#include "host.h"
#include "obj_ray_hit.cl"

kernel void			kernel_ray_trace(
		constant read_only t_obj *objs,
		global read_only uint *objs_size,
		global read_write t_ray_state *ray_states,
		global read_write uint *n_hits,
		global read_only t_config *config)
{

	const int		gid = get_global_id(0);
	t_real			t_nearest;
	t_obj_id		obj_id_nearest;
	t_ray_state		state;

	state = ray_states[gid];
	state.obj_id = -1;
	if (state.importance > config->color_epsilon)
	{
		obj_id_nearest = ray_throw_get_first_hit_obj(config, &state.ray, objs, *objs_size, &t_nearest);
		state.t = (t_nearest < config->z_far) ? t_nearest : -1;
		state.obj_id = obj_id_nearest;
		if (obj_id_nearest > -1)
			atomic_inc(n_hits);
	}
	ray_states[gid] = state;
}
