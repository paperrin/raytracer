/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_real3_rot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 23:36:10 by alngo             #+#    #+#             */
/*   Updated: 2018/01/13 23:45:08 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_real3		ft_real3_rot_z(t_real3 vec, double angle)
{
	t_real3	ret;

	ret.s[0] = vec.s[0] * cos(angle) - vec.s[1] * sin(angle);
	ret.s[1] = vec.s[0] * sin(angle) + vec.s[1] * cos(angle);
	ret.s[2] = vec.s[2];
	return (ret);
}

t_real3		ft_real3_rot_y(t_real3 vec, double angle)
{
	t_real3	ret;

	ret.s[0] = vec.s[0] * cos(angle) + vec.s[2] * sin(angle);
	ret.s[1] = vec.s[1];
	ret.s[2] = -vec.s[0] * sin(angle) + vec.s[2] * cos(angle);
	return (ret);
}

t_real3		ft_real3_rot_x(t_real3 vec, double angle)
{
	t_real3	ret;

	ret.s[0] = vec.s[0];
	ret.s[1] = vec.s[1] * cos(angle) - vec.s[2] * sin(angle);
	ret.s[2] = vec.s[1] * sin(angle) + vec.s[2] * cos(angle);
	return (ret);
}
