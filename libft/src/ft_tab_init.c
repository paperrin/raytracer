/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 13:09:34 by paperrin          #+#    #+#             */
/*   Updated: 2017/03/28 18:22:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tab_init(void **tab, size_t size, ...)
{
	va_list		ap;
	size_t		i;

	va_start(ap, size);
	i = 0;
	while (i < size)
		*(tab + i++) = va_arg(ap, void*);
	va_end(ap);
}
