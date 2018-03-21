#include "shared.h"

kernel void kernel_sum_blocks(
		global read_write uint *ray_hits,
		global read_only uint *group_sums,
		global read_only int *n_elem)
{
	int		gid = get_global_id(0);
	int		group_id = gid / *n_elem;

	ray_hits[gid] += group_sums[group_id - 1];
}
