/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:19:54 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/28 17:55:22 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

void	ft_putwchar_fd(wchar_t wc, int fd)
{
	char	c;
	int		i;

	i = 0;
	while ((c = ft_wchar_char_at(wc, i++)) != -1)
		ft_putchar_fd(c, fd);
}
