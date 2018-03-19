#include "shared.h"

kernel void	kernel_ray_sort(global read_only uint *ray_hits,
							global read_write t_ray_state *ray_states,
							global read_only uint *n_rays,
							local t_ray_state *tmp)
{
	int guid = get_group_id(0);
	int gis = get_global_size(0);
	int gid = get_global_id(0);
	int lid = get_local_id(0);

	if (gid / gis <= guid && gid < *n_rays)
		tmp[lid] = ray_states[gid];
	write_mem_fence(CLK_LOCAL_MEM_FENCE);
	if (gid < *n_rays)
	{
		if (tmp[lid].obj_id > -1)
			ray_states[ray_hits[gid]] = tmp[lid];
	}
}
