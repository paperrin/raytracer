#include "shared.h"

kernel void	kernel_ray_sort(global read_only uint *ray_hits,
							global read_write t_ray_state *ray_states)
{
	int gid = get_global_id(0);
	int lid = get_local_id(0);
	local t_ray_state tmp[256];

	tmp[lid] = ray_states[gid];
	mem_fence(CLK_LOCAL_MEM_FENCE);
	if (tmp[lid].obj_id > -1)
		ray_states[ray_hits[gid] - 1] = tmp[lid];
}
