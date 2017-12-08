/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_multiply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:34:49 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/02 20:42:02 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

static float	cross_multiply(float const *const line, int line_size
		, float const *const col, int col_size)
{
	float	ret;
	int		size;
	int		i;

	ret = 0;
	size = (line_size < col_size ? line_size : col_size);
	i = -1;
	while (++i < size)
		ret += line[i] * col[i * col_size];
	return (ret);
}

void			ft_matrix_multiply(
		t_matrix *dest, t_matrix const *const a, t_matrix const *const b)
{
	int		line;
	int		col;

	if (!(dest && a && b))
		return ;
	line = -1;
	while (++line < MATH_MX_SIZE)
	{
		col = -1;
		while (++col < MATH_MX_SIZE)
		{
			dest->m[col + line * MATH_MX_SIZE] = cross_multiply(
					&a->m[line * MATH_MX_SIZE], MATH_MX_SIZE
					, &b->m[col], MATH_MX_SIZE);
		}
	}
}
