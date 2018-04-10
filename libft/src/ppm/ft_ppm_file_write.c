/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ppm_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:15:01 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/10 20:40:54 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppm.h"

/*
**file.color_depth_vector not freed here!
**fd not closed here either
*/

int			ft_ppm_file_write(t_ppm_file const *const file)
{
	size_t	ret;
	size_t	size;
	char	*header;

	ret = 0;
	size = ((file->max_val <= 255) ? (1) : (2));
	if (!file || !file->color_depth_vector
	|| ft_asprintf(&header, "P%c\n%d %d\n%u\n",
	file->type, file->width, file->height, file->max_val) == -1)
		return (0);
	if ((write(file->fd, header, ft_strlen(header)) !=
				(ssize_t)ft_strlen(header))
	|| ((ret = (ssize_t)write(file->fd, file->color_depth_vector,
	file->height * file->width * 3 * size)) !=
		(ssize_t)file->height * file->width * 3 * size))
	{
		ft_strdel((char **)&header);
		return (0);
	}
	ft_strdel((char **)&header);
	return (1);
}
