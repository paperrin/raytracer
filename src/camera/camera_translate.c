/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_translate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:33:31 by alngo             #+#    #+#             */
/*   Updated: 2018/01/19 00:12:17 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			camera_translate_x(t_camera *cam, t_real amount)
{
	cam->cam_data.pos.s[0] += cam->cam_data.right.s[0] * amount;
	cam->cam_data.pos.s[1] += cam->cam_data.right.s[1] * amount;
	cam->cam_data.pos.s[2] += cam->cam_data.right.s[2] * amount;
}

void			camera_translate_y(t_camera *cam, t_real amount)
{
	cam->cam_data.pos.s[0] += cam->cam_data.up.s[0] * amount;
	cam->cam_data.pos.s[1] += cam->cam_data.up.s[1] * amount;
	cam->cam_data.pos.s[2] += cam->cam_data.up.s[2] * amount;
}

void			camera_translate_z(t_camera *cam, t_real amount)
{
	cam->cam_data.pos.s[0] += cam->cam_data.dir.s[0] * amount;
	cam->cam_data.pos.s[1] += cam->cam_data.dir.s[1] * amount;
	cam->cam_data.pos.s[2] += cam->cam_data.dir.s[2] * amount;
}
