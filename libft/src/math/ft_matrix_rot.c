/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 19:03:20 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/17 18:26:02 by paperrin         ###   ########.fr       */
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

void	ft_matrix_rot(t_matrix *mx, float x, float y, float z)
{
	ft_matrix_rot_x(mx, x);
	ft_matrix_rot_y(mx, y);
	ft_matrix_rot_z(mx, z);
}

void	ft_matrix_rot_axis(t_matrix *const mx, t_vec3f axis, float alpha)
{
	float		ct;
	float		st;
	t_matrix	rot;
	t_matrix	new;

	ct = cos(alpha);
	st = sin(alpha);
	axis = ft_vec3f_norm(axis);
	ft_matrix_to_identity(&rot);
	rot.m[0] = ct + axis.x * axis.x * (1 - ct);
	rot.m[1] = axis.y * axis.x * (1 - ct) + axis.z * st;
	rot.m[2] = axis.z * axis.x * (1 - ct) - axis.y * st;
	rot.m[4] = axis.x * axis.y * (1 - ct) - axis.z * st;
	rot.m[5] = ct + axis.y * axis.y * (1 - ct);
	rot.m[6] = axis.z * axis.y * (1 - ct) + axis.x * st;
	rot.m[8] = axis.x * axis.z * (1 - ct) + axis.y * st;
	rot.m[9] = axis.y * axis.z * (1 - ct) - axis.x * st;
	rot.m[10] = ct + axis.z * axis.z * (1 - ct);
	ft_matrix_multiply(&new, mx, &rot);
	ft_matrix_copy(mx, &new);
}
