/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 16:32:50 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/20 21:20:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "opencl.h"
# include "shared.h"

t_real3		vec3r(t_real x, t_real y, t_real z);
cl_float3	vec3f(cl_float x, cl_float y, cl_float z);

#endif
