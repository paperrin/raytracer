/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 01:18:13 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 01:25:06 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_putfloat(long double nb)
{
	char		*str;

	if (!(str = ft_ftoa(nb, 6, ".")))
		return (0);
	ft_putstr(str);
	ft_strdel(&str);
	return (1);
}
