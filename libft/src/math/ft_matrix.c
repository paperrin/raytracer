/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:48:16 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/16 22:26:12 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>

t_matrix	*ft_matrix_new(void)
{
	t_matrix	*ret;

	ret = (t_matrix*)malloc(sizeof(t_matrix));
	return (ret);
}

void		ft_matrix_to_identity(t_matrix *const mx)
{
	int		i;

	if (mx)
	{
		i = -1;
		while (++i < MATH_MX_SIZE * MATH_MX_SIZE)
			mx->m[i] = (i % (MATH_MX_SIZE + 1) == 0);
	}
}

t_matrix	*ft_matrix_copy(t_matrix *dst, t_matrix const *const src)
{
	int		i;

	if (!src || !dst)
		return (NULL);
	i = -1;
	while (++i < MATH_MX_SIZE * MATH_MX_SIZE)
		dst->m[i] = src->m[i];
	return (dst);
}

void		ft_matrix_del(t_matrix **mx)
{
	if (mx)
		ft_memdel((void**)mx);
}
