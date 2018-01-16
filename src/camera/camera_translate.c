/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_translate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:33:31 by alngo             #+#    #+#             */
/*   Updated: 2018/01/17 00:00:40 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_real3			matrix_real3_mult(t_real16 *mat, t_real3 *vec)
{
	t_real3		ret;

	ret.s[0] = vec->s[0] * mat->s[0] + vec->s[1] * mat->s[4] + vec->s[2] * mat->s[8] + mat->s[3];
	ret.s[1] = vec->s[0] * mat->s[1] + vec->s[1] * mat->s[5] + vec->s[2] * mat->s[9] + mat->s[7];
	ret.s[2] = vec->s[0] * mat->s[2] + vec->s[1] * mat->s[6] + vec->s[2] * mat->s[10] + mat->s[11];
	return (ret);
}

void			camera_translate_x(t_camera *cam, t_real amount)
{
	matrix_real16_translate(&cam->mat, amount, 0, 0);
	cam->cam_data.pos = matrix_real3_mult(&cam->mat, &cam->cam_data.pos);
}

void			camera_translate_y(t_camera *cam, t_real amount)
{
	matrix_real16_translate(&cam->mat, 0, amount, 0);
	cam->cam_data.pos = matrix_real3_mult(&cam->mat, &cam->cam_data.pos);
}

void			camera_translate_z(t_camera *cam, t_real amount)
{
	matrix_real16_translate(&cam->mat, 0, 0, amount);
	cam->cam_data.pos = matrix_real3_mult(&cam->mat, &cam->cam_data.pos);
}
