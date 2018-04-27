#include "host.h"

kernel void		kernel_clear(
	global write_only cl_float *pixels)
{
	const int		gid = get_global_id(0);

	pixels[gid * 4 + 0] = 0;
	pixels[gid * 4 + 1] = 0;
	pixels[gid * 4 + 2] = 0;
	pixels[gid * 4 + 3] = 1;
}
