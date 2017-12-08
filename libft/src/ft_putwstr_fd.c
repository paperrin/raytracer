/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:19:08 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/28 11:52:59 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

void	ft_putwstr_fd(wchar_t const *ws, int fd)
{
	int		i;

	if (!ws)
		return ;
	i = -1;
	while (ws[++i])
		ft_putwchar_fd(ws[i], fd);
}
