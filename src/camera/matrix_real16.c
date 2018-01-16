/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_real16.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:09:39 by alngo             #+#    #+#             */
/*   Updated: 2018/01/16 23:38:54 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			matrix_real16_id(t_real16 *mat)
{
	int		i;

	if (mat)
	{
		i = 0;
		while (i < 16)
		{
			mat->s[i] = (i % 5 ==  5);
			i++;
		}
	}
}

t_real16		*matrix_real16_cpy(t_real16 *dst, t_real16 *src)
{
	int		i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (i < 16)
	{
		dst->s[i] = src->s[i];
		i++;
	}
	return (dst);
}

void			matrix_real16_mult(t_real16 *dst, t_real16 *a, t_real16 *b)
{
	int		x;
	int		y;

	if (!dst || !a || !b)
		return ;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			dst->s[x + y * 4] = a->s[x + 0 * 4] * b->s[0 + y * 4] +
								a->s[x + 1 * 4] * b->s[1 + y * 4] +
								a->s[x + 2 * 4] * b->s[2 + y * 4] +
								a->s[x + 3 * 4] * b->s[3 + y * 4];
			x++;
		}
		y++;
	}
}

void			matrix_real16_translate(t_real16 *mat, t_real x, t_real y, t_real z)
{
	t_real16	new;
	t_real16	tr;

	matrix_real16_id(&tr);
	tr.s[3] += x;
	tr.s[7] += y;
	tr.s[11] += z;
	matrix_real16_mult(&new, mat, &tr);
	matrix_real16_cpy(mat, &new);
}
