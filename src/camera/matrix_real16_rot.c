/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_real16_rot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:48:23 by alngo             #+#    #+#             */
/*   Updated: 2018/01/20 21:48:26 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			matrix_real16_rot_x(t_real16 *mat, double alpha)
{
	t_real16	new;
	t_real16	rot;

	matrix_real16_id(&rot);
	rot.s[5] = cos(alpha);
	rot.s[6] = -sin(alpha);
	rot.s[9] = sin(alpha);
	rot.s[10] = cos(alpha);
	matrix_real16_mult(&new, mat, &rot);
	matrix_real16_cpy(mat, &new);
}

void			matrix_real16_rot_y(t_real16 *mat, double alpha)
{
	t_real16	new;
	t_real16	rot;

	matrix_real16_id(&rot);
	rot.s[0] = cos(alpha);
	rot.s[2] = sin(alpha);
	rot.s[8] = -sin(alpha);
	rot.s[10] = cos(alpha);
	matrix_real16_mult(&new, mat, &rot);
	matrix_real16_cpy(mat, &new);
}

void			matrix_real16_rot_z(t_real16 *mat, double alpha)
{
	t_real16	new;
	t_real16	rot;

	matrix_real16_id(&rot);
	rot.s[0] = cos(alpha);
	rot.s[1] = -sin(alpha);
	rot.s[4] = sin(alpha);
	rot.s[5] = cos(alpha);
	matrix_real16_mult(&new, mat, &rot);
	matrix_real16_cpy(mat, &new);
}
