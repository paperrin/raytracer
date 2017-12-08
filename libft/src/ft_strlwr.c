/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlwr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 14:56:06 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/11 14:56:38 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		to_lower(char *c)
{
	*c = ft_tolower(*c);
}

char			*ft_strlwr(char *str)
{
	ft_striter(str, &to_lower);
	return (str);
}
