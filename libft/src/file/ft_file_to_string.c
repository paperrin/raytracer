/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:14:21 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/18 18:17:36 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file.h"

static char		*copy_to_str(const char *const file_path, char *str,
		ssize_t size)
{
	char		buf[4096];
	int			fd;
	ssize_t		n;
	ssize_t		i;

	if ((fd = open(file_path, O_RDONLY)) < 0)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while ((n = read(fd, buf, 4096)) > 0)
	{
		if (i + n > size)
			break ;
		ft_strncpy(&str[i], buf, n);
		i += n;
	}
	if (close(fd) < 0 || i != size)
	{
		free(str);
		return (NULL);
	}
	str[i] = '\0';
	return (str);
}

char			*ft_file_to_string(const char *const file_path)
{
	ssize_t		size;
	char		*str;

	if ((size = ft_file_get_size(file_path)) < 0)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	return (copy_to_str(file_path, str, size));
}
