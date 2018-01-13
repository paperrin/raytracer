/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_translate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:33:31 by alngo             #+#    #+#             */
/*   Updated: 2018/01/13 23:48:32 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			camera_translate_x(t_camera *cam, t_real amount)
{
	cam->pos.s[0] += amount;
}

void			camera_translate_y(t_camera *cam, t_real amount)
{
	cam->pos.s[1] += amount;
}

void			camera_translate_z(t_camera *cam, t_real amount)
{
	cam->pos.s[0] += cam->dir.s[0] * amount;
	cam->pos.s[1] += cam->dir.s[1] * amount;
	cam->pos.s[2] += cam->dir.s[2] * amount;
}
