/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:25:38 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/16 15:43:21 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

/*
** Please care of data packing when changing data types / structure order
*/

typedef t_real			cl_float;
typedef t_real2			cl_float2;
typedef t_real3			cl_float3;
typedef t_real4			cl_float4;
typedef t_real8			cl_float8;
typedef t_real16		cl_float16;

typedef t_obj_type		cl_short;
typedef t_mat_id		cl_short;

typedef struct			s_plane
{
	t_real3				pos;
	t_real3				up;
	t_real3				normal;
}						t_plane;

typedef struct			s_sphere
{
	t_real3				pos;
	t_real3				normal;
	t_real				radius;
}						t_sphere;

typedef struct			s_cylinder
{
	t_real3				pos;
	t_real3				up;
	t_real3				normal;
	t_real				radius;
}						t_cylinder;

typedef struct			s_cone
{
	t_real3				pos;
	t_real3				up;
	t_real3				normal;
	t_real				radius;
}						t_cone;

typedef union			u_obj_container
{
	t_plane				plane;
	t_sphere			sphere;
	t_cylinder			cylinder;
	t_cone				cone;
}						t_obj_container;

typedef struct			s_obj
{
	t_obj_type			type;
	t_mat_id			material;
	t_obj_container		as;
}						t_obj;

typedef struct			s_camera
{
	t_real3				pos;
	t_real3				dir;
	t_real3				up;
	t_real3				right;
}						t_camera;

typedef struct			s_view
{
	cl_int2				pos;
	cl_uint2			size;
}						t_view;

#endif
