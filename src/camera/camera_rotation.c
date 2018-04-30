/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:52:46 by alngo             #+#    #+#             */
/*   Updated: 2018/04/18 02:41:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_real3		matrix_real3_rot(t_real16 *mat, t_real3 vec)
{
	t_real3	ret;

	ret.s[0] = vec.s[0] * mat->s[0]
			+ vec.s[1] * mat->s[1]
			+ vec.s[2] * mat->s[2];
	ret.s[1] = vec.s[0] * mat->s[4]
			+ vec.s[1] * mat->s[5]
			+ vec.s[2] * mat->s[6];
	ret.s[2] = vec.s[0] * mat->s[8]
			+ vec.s[1] * mat->s[9]
			+ vec.s[2] * mat->s[10];
	return (ret);
}
