/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_real.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:03:23 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 18:13:41 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_REAL_H
# define T_REAL_H

# ifdef IS_KERNEL
typedef	float			cl_float;
typedef	float2			cl_float2;
typedef	float3			cl_float3;
typedef	float4			cl_float4;
typedef	float8			cl_float8;
typedef	float16			cl_float16;
typedef	double			cl_double;
typedef	double2			cl_double2;
typedef	double3			cl_double3;
typedef	double4			cl_double4;
typedef	double8			cl_double8;
typedef	double16		cl_double16;
typedef char			cl_uchar;
typedef short			cl_short;
typedef int				cl_int;
typedef int2			cl_int2;
typedef uint			cl_uint;
typedef uint2			cl_uint2;
typedef long			cl_long;
typedef unsigned long	cl_ulong;
typedef uchar3			cl_uchar3;
# endif

# ifdef DOUBLE_SUPPORT_AVAILABLE
#  define REAL_MAX DBL_MAX
#  define REAL_MIN DBL_MIN
typedef cl_double		t_real;
typedef cl_double2		t_real2;
typedef cl_double3		t_real3;
typedef cl_double4		t_real4;
typedef cl_double8		t_real8;
typedef cl_double16		t_real16;
# else
#  define REAL_MAX FLT_MAX
#  define REAL_MIN FLT_MIN
typedef cl_float		t_real;
typedef cl_float2		t_real2;
typedef cl_float3		t_real3;
typedef cl_float4		t_real4;
typedef cl_float8		t_real8;
typedef cl_float16		t_real16;
# endif

#endif
