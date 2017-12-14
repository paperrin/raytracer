/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_get_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:14:13 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/13 17:28:16 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file.h"

ssize_t		ft_file_get_size(const char *const file_path)
{
	char		buf[4096];
	ssize_t		n;
	ssize_t		size;
	int			fd;

	if ((fd = open(file_path, O_RDONLY)) < 0)
		return (fd);
	size = 0;
	while ((n = read(fd, buf, 4096)) > 0)
		size += n;
	if (n != 0)
		size = n;
	if (close(fd) < 0)
		return (-1);
	return (size);
}
