#include "shared.h"

int					find_texel_id(global read_only t_texel *texels, global read_only uint *size, int px_id);

kernel void			kernel_combine_texels(
		constant read_only uint2 *screen_size,
		global read_only t_texel *texels,
		global read_only uint *texels_size,
		global write_only cl_float *pixels)
{
	const int		gid = get_global_id(0);
	int				i;

	if ((i = find_texel_id(texels, texels_size, gid)) > -1)
	{
		pixels[gid * 4 + 0] = texels[i].r;
		pixels[gid * 4 + 1] = texels[i].g;
		pixels[gid * 4 + 2] = texels[i].b;
		pixels[gid * 4 + 3] = 1;
	}
	else
	{
		pixels[gid * 4 + 0] = 0;
		pixels[gid * 4 + 1] = 0;
		pixels[gid * 4 + 2] = 0;
		pixels[gid * 4 + 3] = 1;
	}

	/*
	pixels[texels[gid].px_id * 4 + 0] = texels[gid].r;
	pixels[texels[gid].px_id * 4 + 1] = texels[gid].g;
	pixels[texels[gid].px_id * 4 + 2] = texels[gid].b;
	pixels[texels[gid].px_id * 4 + 3] = 1;
	*/
}

int					find_texel_id(global read_only t_texel *texels, global read_only uint *size, int px_id)
{
	int		middle;
	int		start;
	int		end;

	start = 0;
	end = *size - 1;
	while (start <= end)
	{
		middle = (start + end) / 2;
		if (px_id < texels[middle].px_id)
			end = middle - 1;
		else if (px_id > texels[middle].px_id)
			start = middle + 1;
		else
			return (middle);
	}
	return (-1);
}
