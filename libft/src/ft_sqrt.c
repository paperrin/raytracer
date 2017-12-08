/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 14:56:26 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/17 15:15:41 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_near_sqrt(int nb)
{
	int		sr;

	sr = 0;
	while (sr * sr < nb)
		sr++;
	if (sr * sr == nb)
		return (sr);
	else if (sr > 0)
		return (sr - 1);
	return (0);
}

int		ft_sqrt(int nb)
{
	int		sr;

	sr = ft_near_sqrt(nb);
	if (sr * sr == nb)
		return (sr);
	return (0);
}
