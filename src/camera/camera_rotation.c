/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:52:46 by alngo             #+#    #+#             */
/*   Updated: 2018/01/16 23:20:39 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		camera_rotation_x(t_camera_data *cam, double angle)
{
	cam->dir = ft_real3_rot_x(cam->dir, angle);
	cam->up = ft_real3_rot_x(cam->up, angle);
	cam->right = ft_real3_rot_x(cam->right, angle);
}

void		camera_rotation_y(t_camera_data *cam, double angle)
{
	cam->dir = ft_real3_rot_y(cam->dir, angle);
	cam->up = ft_real3_rot_y(cam->up, angle);
	cam->right = ft_real3_rot_y(cam->right, angle);
}

void		camera_rotation_z(t_camera_data *cam, double angle)
{
	cam->dir = ft_real3_rot_z(cam->dir, angle);
	cam->up = ft_real3_rot_z(cam->up, angle);
	cam->right = ft_real3_rot_z(cam->right, angle);
}
