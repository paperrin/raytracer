#include "shared.h"

kernel void			kernel_ray_gen_next(
		global read_only t_ray_state *ray_states,
		global read_only t_hit *hits,
		constant read_only t_obj *objs,
		global write_only t_ray_state *new_ray_states)
{
}
