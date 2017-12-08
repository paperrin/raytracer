/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 14:44:09 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/11 14:55:57 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		to_upper(char *c)
{
	*c = ft_toupper(*c);
}

char			*ft_strupr(char *str)
{
	ft_striter(str, &to_upper);
	return (str);
}
