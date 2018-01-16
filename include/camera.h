/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:42:32 by alngo             #+#    #+#             */
/*   Updated: 2018/01/16 23:59:33 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct			s_camera
{
	t_camera_data		cam_data;
	t_real16			mat;
}						t_camera;


void			camera_init(t_camera *cam);
void			camera_translate_x(t_camera *cam, t_real amount);
void			camera_translate_y(t_camera *cam, t_real amount);
void			camera_translate_z(t_camera *cam, t_real amount);

void			camera_rotation_x(t_camera_data *cam, double angle);
void			camera_rotation_y(t_camera_data *cam, double angle);
void			camera_rotation_z(t_camera_data *cam, double angle);

t_real3			ft_real3_rot_x(t_real3 vec, double angle);
t_real3			ft_real3_rot_y(t_real3 vec, double angle);
t_real3			ft_real3_rot_z(t_real3 vec, double angle);

t_real3			matrix_real3_mult(t_real16 *mat, t_real3 *vec);

void			matrix_real16_id(t_real16 *mat);
t_real16		*matrix_real16_cpy(t_real16 *dst, t_real16 *src);
void			matrix_real16_mult(t_real16 *dst, t_real16 *a, t_real16 *b);
void			matrix_real16_translate(t_real16 *mat, t_real x, t_real y, t_real z);
void			matrix_real16_rot_x(t_real16 *mat, double alpha);
void			matrix_real16_rot_y(t_real16 *mat, double alpha);
void			matrix_real16_rot_z(t_real16 *mat, double alpha);
#endif
