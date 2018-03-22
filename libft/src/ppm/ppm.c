/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 06:46:39 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/22 22:36:51 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppm.h"
#include <stdio.h>
/*
**read_to_any_char should accept all WHITESPACES
*//*
static int		ignore_comment(t_fstream *file, )
static int		read_header(t_fstream *file, size_t *const width,
		size_t *const height, unsigned int *const max_val)
{
	int		ret;
	char	*line;
	int		line_nb;
	char	*prev_line;

	prev_line = NULL;
	line_nb = 0;
	while ((ret = ft_fstream_sread_to_any_char(file, &line, "\v\f\n\t\r ", 1)) > 0)
	{
		if (prev_line)
			free(prev_line);
		prev_line = line;
		if (*line == '#')
			continue ;
		while (ft_is_whitespace((int)*line))
			line++;
		if (line_nb == 0 && ft_strstr(line, "P6") == line && ++line_nb)
			continue ;
		else if (line_nb == 0)
			break ;
	
		if (line_nb == 1 && *line != '\0')
		{
			*width = ft_atoi(line);
			while (ft_isdigit((int)*line))
				line++;
			while (ft_is_whitespace((int)*line))
				line++;
			*height = ft_atoi(line);
			if (*width > 0 && *height > 0)
				line_nb++;
			continue ;
		}
		if (line_nb == 2 && ft_strchr_any(line, "0123456789"))
		{
			*max_val = ft_atoi(line);
			if (*max_val <= 0 || *max_val >= 65536)
				break ;
			line_nb++;
			break ;
		}
	}
	if (prev_line)
		free(prev_line);
	return (line_nb == 3 && ret != -1);
}
*/
static int		read_raster(t_fstream *file, size_t const *const dim, int bytes_per_color, char *const pixels)
{
	long		ret;
	size_t		bytes_len;
	size_t		bytes_left;

	bytes_len = file->read_buf_n_bytes - file->read_offset;
	bytes_left = dim[0] * dim[1] * bytes_per_color - bytes_len;
	ft_memcpy(pixels, &file->read_buf[file->read_offset], bytes_len);
	if ((ret = read(file->fd, &pixels[bytes_len], bytes_left)) < 0)
		return (0);
	return (1);
}

char			*ft_ppm_get(char const *const path, size_t *const width,
		size_t *const height, unsigned int *const max_val)
{
	t_fstream		*file;
	size_t			dim[2];
	char			*pixels;
	int				bytes_per_color;

	if (!(file = ft_fstream_read_open(path)))
	{
		ft_printf("Usage : ./rt filepath\n");
		return (NULL);
	}
	if (!ft_ppm_read_header(file, width, height, max_val))
	{
		ft_printf("ppm| invalid file\n");
		return (NULL);
	}
	bytes_per_color = (*max_val > 255 ? 2 : 1) * 3 * sizeof(char);
	if ((pixels = (char*)malloc(sizeof(char) * bytes_per_color * *width * *height)))
	{
		dim[0] = *width;
		dim[1] = *height;
		if (!read_raster(file, dim, bytes_per_color, pixels))
			ft_memdel((void**)&pixels);
	}
	ft_fstream_close(&file);
	return (pixels);
}
