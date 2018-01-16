/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:04:34 by alngo             #+#    #+#             */
/*   Updated: 2018/01/16 23:20:43 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		camera_init(t_camera *cam)
{
	cam->cam_data.pos = vec3r(0, 0, -2.5);
	cam->cam_data.dir = vec3r(0, 0, 1);
	cam->cam_data.up = vec3r(0, 1, 0);
	cam->cam_data.right = vec3r(1, 0, 0);
	matrix_real16_id(&cam->mat);
}
