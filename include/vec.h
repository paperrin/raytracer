/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 16:32:50 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/16 23:32:13 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "opencl.h"
# include "shared.h"
# include "ft_math.h"

t_real3		vec3r(t_real x, t_real y, t_real z);
t_real		vec3r_dot(t_real3 a, t_real3 b);
t_real		vec3r_mag(t_real3 vec);
t_real3		vec3r_norm(t_real3 vec);
t_real3		vec3r_matrix_rot(t_real3 v3r, t_matrix const *const mx);

cl_float3	vec3f(cl_float x, cl_float y, cl_float z);

t_real2		vec2r(t_real x, t_real y);

#endif
