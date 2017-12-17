#include "shared.h"

kernel void			kernel_ray_trace(
		global read_only t_ray_state *ray_states,
		constant read_only t_obj *objs,
		constant read_only uint *objs_size,
		global write_only t_hit *hits)
{

}
