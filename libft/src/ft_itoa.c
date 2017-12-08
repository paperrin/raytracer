/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 12:59:15 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/11 13:38:42 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_uitoa(uintmax_t nb)
{
	return (ft_uitoa_base(nb, 10));
}

char			*ft_itoa(intmax_t nb)
{
	return (ft_itoa_base(nb, 10));
}
