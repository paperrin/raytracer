#include "shared.h"

__kernel void kernel_ray_gen(__constant t_camera cam, __constant uint2 screen_size,
		__global float3 *dir)
{
	const int		id = get_global_id(0);	
}
