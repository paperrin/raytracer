#include "shared.h"

kernel void			kernel_compute_texels(
		global read_only t_ray_state *ray_states,
		global read_only t_hit *hits,
		constant read_only t_obj *objs,
		global write_only cl_float3 *texels)
{
}
