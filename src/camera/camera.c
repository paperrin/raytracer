/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:04:34 by alngo             #+#    #+#             */
/*   Updated: 2018/01/19 18:22:57 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			camera_update(t_camera *cam)
{
	t_real16	mat;

	cam->cam_data.dir = vec3r(0, 0, 1);
	cam->cam_data.up = vec3r(0, 1, 0);
	cam->cam_data.right = vec3r(1, 0, 0);
	matrix_real16_id(&mat);
	matrix_real16_rot_x(&mat, cam->rot.s[0]);
	matrix_real16_rot_y(&mat, cam->rot.s[1]);
	matrix_real16_rot_z(&mat, cam->rot.s[2]);
	cam->cam_data.dir = matrix_real3_rot(&mat, vec3r(0, 0, 1));
	cam->cam_data.up = matrix_real3_rot(&mat, vec3r(0, 1, 0));
	cam->cam_data.right = matrix_real3_rot(&mat, vec3r(1, 0, 0));
}
