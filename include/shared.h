/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:25:38 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/17 21:44:19 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

/*
** Please care of data packing when changing data types / structure order
*/


# ifdef IS_KERNEL

typedef	float			cl_float;
typedef	float2			cl_float2;
typedef	float3			cl_float3;
typedef	float4			cl_float4;
typedef	float8			cl_float8;
typedef	float16			cl_float16;
typedef char			cl_uchar;
typedef short			cl_short;
typedef int				cl_int;
typedef int2			cl_int2;
typedef uint			cl_uint;
typedef uint2			cl_uint2;

# endif

typedef cl_float		t_real;
typedef cl_float2		t_real2;
typedef cl_float3		t_real3;
typedef cl_float4		t_real4;
typedef cl_float8		t_real8;
typedef cl_float16		t_real16;

typedef cl_short		t_obj_type;
typedef cl_int			t_obj_id;
typedef cl_short		t_mat_id;

typedef enum			e_obj_type
{
	type_sphere,
	type_plane,
	type_cylinder,
	type_cone
}						t_e_obj_type;

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
	t_real				pxl_ratio;
}						t_camera;

typedef struct			s_ray
{
	t_real3				origin;
	t_real3				dir;
}						t_ray;

typedef struct			s_hit
{
	t_obj_id			obj_id;
	t_real				t;
}						t_hit;

typedef struct			s_ray_state
{
	t_ray				ray;
	cl_uchar			view_id;
	cl_uint				pxl_id;
	cl_uchar			type;
}						t_ray_state;

#endif
