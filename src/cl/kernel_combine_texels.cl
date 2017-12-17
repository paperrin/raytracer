#include "shared.h"

kernel void			kernel_combine_texels(
		constant read_only uint2 *screen_size,
		constant read_only t_cam *cam,
		global read_only cl_float3 *texels,
		global write_only cl_float3 *pixels)
{
}
