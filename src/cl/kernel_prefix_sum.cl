#include "shared.h"

kernel void	kernel_prefix_sum(global read_write uint *ray_hits, constant read_only t_prefix_sums *prefix_sums)
{
	int gid = get_global_id(0);
	int left, right;

	right = prefix_sums->start + gid * prefix_sums->step;
	left = right - prefix_sums->offset;
	if (right < prefix_sums->arr_size)
		ray_hits[right] += ray_hits[left];
}
