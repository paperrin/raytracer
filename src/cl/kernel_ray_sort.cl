#include "shared.h"

kernel void	kernel_ray_sort(global read_only uint *ray_hits,
							global read_write t_ray_state *ray_states,
							global read_only uint *n_rays,
							local t_ray_state *tmp,
							local t_ray_state *l_data)
{
	int		l_size = get_local_size(0);
	int		lid = get_local_id(0);
	int		group_id;
	int		group_nb;
	int		gid;

	group_nb = *n_rays / l_size + (*n_rays % l_size != 0);
	group_id = -1;
	while (++group_id < group_nb)
	{
		gid = group_id * l_size + lid;
		if (gid >= *n_rays)
			continue ;
		l_data[lid] = ray_states[gid];
		tmp[lid] = l_data[lid];
		write_mem_fence(CLK_LOCAL_MEM_FENCE);

			printf("(%d: %d)>>", gid, tmp[lid].obj_id);
		if (tmp[lid].obj_id > -1)
		{
			printf("(%d: %d)\n", gid, tmp[lid].obj_id);
			ray_states[ray_hits[gid]] = tmp[lid];
		}
		else
			printf("\n");
		write_mem_fence(CLK_GLOBAL_MEM_FENCE);
	}
}
