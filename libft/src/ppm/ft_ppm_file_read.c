/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ppm_file_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:59:47 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/28 20:11:19 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ppm.h"

static int		read_raster(t_fstream *file, size_t const *const dim,
				int bytes_per_color, unsigned char *const pixels)
{
	long			ret;
	ssize_t			bytes_len;
	ssize_t			bytes_left;
	const size_t	image_bytes_len = dim[0] * dim[1] * bytes_per_color;

	bytes_len = file->read_buf_n_bytes - file->read_offset;
	if (bytes_len > (ssize_t)image_bytes_len)
		bytes_len = image_bytes_len;
	bytes_left = image_bytes_len - bytes_len;
	ft_memcpy(pixels, &file->read_buf[file->read_offset], bytes_len);
	if (bytes_left <= 0)
		return (1);
	if ((ret = read(file->fd, &pixels[bytes_len], bytes_left)) < 0)
		return (0);
	if (bytes_left != 0 && ret != bytes_left)
		return (0);
	return (1);
}

unsigned char	*ft_ppm_file_read(char const *const path, size_t *const width,
		size_t *const height, unsigned int *const max_val)
{
	t_fstream		*file;
	size_t			dim[2];
	unsigned char	*pixels;
	int				bytes_per_color;

	if (!(file = ft_fstream_read_open(path)))
		return (NULL);
	if (!ft_ppm_read_header(file, width, height, max_val))
		return (NULL);
	bytes_per_color = (*max_val > 255 ? 2 : 1) * 3 * sizeof(char);
	if ((pixels = (unsigned char*)malloc(
					bytes_per_color * *width * *height)))
	{
		dim[0] = *width;
		dim[1] = *height;
		if (!read_raster(file, dim, bytes_per_color, pixels))
			ft_memdel((void**)&pixels);
	}
	ft_fstream_close(&file);
	return (pixels);
}
