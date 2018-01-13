/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:42:32 by alngo             #+#    #+#             */
/*   Updated: 2018/01/13 23:28:11 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

void		camera_translate_x(t_camera *cam, t_real amount);
void		camera_translate_y(t_camera *cam, t_real amount);
void		camera_translate_z(t_camera *cam, t_real amount);

void		camera_rotation_x(t_camera *cam, double angle);
void		camera_rotation_y(t_camera *cam, double angle);
void		camera_rotation_z(t_camera *cam, double angle);

t_real3		ft_real3_rot_x(t_real3 vec, double angle);
t_real3		ft_real3_rot_y(t_real3 vec, double angle);
t_real3		ft_real3_rot_z(t_real3 vec, double angle);

#endif
