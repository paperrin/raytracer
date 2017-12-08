/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:32:41 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 17:01:38 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "my_unistd.h"

void	ft_putnstr_fd(char const *s, size_t n, int fd)
{
	if (!s)
		return ;
	write(fd, s, n);
}
