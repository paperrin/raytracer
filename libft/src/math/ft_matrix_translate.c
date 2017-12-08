/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_translate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 19:02:02 by paperrin          #+#    #+#             */
/*   Updated: 2017/03/28 19:50:43 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

void	ft_matrix_translate(t_matrix *mx, float x, float y, float z)
{
	t_matrix new;
	t_matrix tr;

	ft_matrix_to_identity(&tr);
	tr.m[3] += x;
	tr.m[7] += y;
	tr.m[11] += z;
	ft_matrix_multiply(&new, mx, &tr);
	ft_matrix_copy(mx, &new);
}
