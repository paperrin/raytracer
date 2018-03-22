#include "shared.h"

kernel void kernel_ray_sort(
		global read_only uint *prefix_sum,
		global read_write t_ray_state *ray_states,
		global read_only uint *n_rays,
		local read_write t_ray_state *tmp)
{
	int			l_size = get_local_size(0);
	int			l_id = get_local_id(0);
	int			group_id = -1;
	int			group_nb = *n_rays / l_size + (*n_rays % l_size == 1);
	int			state_id;
	uint		new_id;

	while (++group_id < group_nb)
	{
		state_id = group_id * l_size + l_id;
		if (state_id < *n_rays)
		{
			tmp[l_id] = ray_states[state_id];
			ray_states[state_id].obj_id = -1;
			new_id = prefix_sum[state_id];
		}
		mem_fence(CLK_GLOBAL_MEM_FENCE | CLK_LOCAL_MEM_FENCE);
		if (state_id < *n_rays)
		{
			if (tmp[l_id].obj_id > -1)
				ray_states[new_id] = tmp[l_id];
		}
		mem_fence(CLK_GLOBAL_MEM_FENCE);
	}
}
