#include "shared.h"

kernel void kernel_prefix_sum(
		global read_write uint *ray_hits,
		local read_write uint *tmp,
		global read_only int *n,
		global write_only uint *group_sums)
{
	int gid = get_global_id(0);
	int lid = get_local_id(0);
	int	wg_size = *n / 2;
	int	group_id = gid / wg_size;
	int offset = 1;
	int a, b, d;
	uint t;
	
	tmp[2 * lid] = ray_hits[2 * gid];
	tmp[2 * lid + 1] = ray_hits[2 * gid + 1];
	d = *n / 2;
	while (d > 0)
	{
		write_mem_fence(CLK_LOCAL_MEM_FENCE);
		if (lid < d)
		{
			a = offset * (2 * lid + 1) - 1;
			b = offset * (2 * lid + 2) - 1;
			tmp[b] += tmp[a];
		}
		offset *= 2;
		d /= 2;
	}
	if (lid == 0)
		tmp[*n - 1] = 0;
	d = 1;
	while (d < *n)
	{
		offset /= 2;
		write_mem_fence(CLK_LOCAL_MEM_FENCE);
		if (lid < d)
		{
			a = offset * (2 * lid + 1) - 1;
			b = offset * (2 * lid + 2) - 1;
			t = tmp[a];
			tmp[a] = tmp[b];
			tmp[b] += t;
		}
		d *= 2;
	}
	write_mem_fence(CLK_LOCAL_MEM_FENCE);
	if (lid == *n / 2 - 1)
	{
		group_sums[group_id] = tmp[*n - 1] + tmp[1];
	}
	ray_hits[2 * gid] = tmp[2 * lid];
	ray_hits[2 * gid + 1] = tmp[2 * lid + 1];
}
