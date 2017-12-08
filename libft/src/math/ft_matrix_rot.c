/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 19:03:20 by paperrin          #+#    #+#             */
/*   Updated: 2017/03/27 15:49:03 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

void	ft_matrix_rot_x(t_matrix *mx, float alpha)
{
	t_matrix new;
	t_matrix rot;

	ft_matrix_to_identity(&rot);
	rot.m[5] = cos(alpha);
	rot.m[6] = -sin(alpha);
	rot.m[9] = sin(alpha);
	rot.m[10] = cos(alpha);
	ft_matrix_multiply(&new, mx, &rot);
	ft_matrix_copy(mx, &new);
}

void	ft_matrix_rot_y(t_matrix *mx, float alpha)
{
	t_matrix new;
	t_matrix rot;

	ft_matrix_to_identity(&rot);
	rot.m[0] = cos(alpha);
	rot.m[2] = sin(alpha);
	rot.m[8] = -sin(alpha);
	rot.m[10] = cos(alpha);
	ft_matrix_multiply(&new, mx, &rot);
	ft_matrix_copy(mx, &new);
}

void	ft_matrix_rot_z(t_matrix *mx, float alpha)
{
	t_matrix new;
	t_matrix rot;

	ft_matrix_to_identity(&rot);
	rot.m[0] = cos(alpha);
	rot.m[1] = -sin(alpha);
	rot.m[4] = sin(alpha);
	rot.m[5] = cos(alpha);
	ft_matrix_multiply(&new, mx, &rot);
	ft_matrix_copy(mx, &new);
}
