/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:25:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/02/17 20:58:49 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

/*
** Please care of data packing when changing data types / structure order
*/

# ifdef CONFIG_USE_DOUBLE
#  ifdef cl_khr_fp64
#   pragma OPENCL EXTENSION cl_khr_fp64 : enable
#   define DOUBLE_SUPPORT_AVAILABLE
#  elif defined cl_amd_fp64
#   pragma OPENCL EXTENSION cl_amd_fp64 : enable
#   define DOUBLE_SUPPORT_AVAILABLE
#  endif
# endif

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
typedef cl_double		t_real;
typedef cl_double2		t_real2;
typedef cl_double3		t_real3;
typedef cl_double4		t_real4;
typedef cl_double8		t_real8;
typedef cl_double16		t_real16;
#define REAL_MAX DBL_MAX
#define REAL_MIN DBL_MIN
# else
typedef cl_float		t_real;
typedef cl_float2		t_real2;
typedef cl_float3		t_real3;
typedef cl_float4		t_real4;
typedef cl_float8		t_real8;
typedef cl_float16		t_real16;
#define REAL_MAX FLT_MAX
#define REAL_MIN FLT_MIN
# endif

typedef cl_short		t_obj_type;
typedef cl_int			t_obj_id;
typedef cl_short		t_mat_id;

typedef struct			s_camera_data
{
	t_real3				pos;
	t_real3				dir;
	t_real3				up;
	t_real3				right;
	t_real				pxl_ratio;
}						t_camera_data;

typedef struct			s_config
{
	cl_float3			ambient;
	cl_uint2			screen_size;
	cl_int				max_depth;
	cl_int				cur_depth;
}						t_config;

/*
** Rays
*/

typedef struct			s_ray
{
	t_real3				origin;
	t_real3				dir;
}						t_ray;

typedef struct			s_ray_state
{
	t_ray				ray;
	t_real				t;
	cl_float			importance;
	cl_uint				pxl_id;
	t_obj_id			obj_id;
}						t_ray_state;

/*
** Objects
*/

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
	t_real3				up;
	t_real3				front;
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
	t_mat_id			material_id;
	t_obj_container		as;
}						t_obj;

typedef struct			s_material
{
	cl_float3			color;
	cl_float			reflection;
	cl_float			refraction;
	cl_float			indice_of_refraction;
	cl_int				texture_id;
}						t_material;

typedef enum			e_filter
{
	e_filter_nearest = 0,
	e_filter_bilinear
}						t_filter;

typedef struct			s_texture
{
	cl_long				pixels_offset;
	cl_uint				width;
	cl_uint				height;
	t_filter			filter;

}						t_texture;

/*
** Lights
*/

typedef enum			e_light_type
{
	light_type_point,
	light_type_spot,
	light_type_dir
}						t_light_type;

typedef struct			s_light_point
{
	t_real3				pos;
}						t_light_point;

typedef struct			s_light_spot
{
	t_real3				pos;
	t_real3				dir;
	t_real				beam_angle;
	t_real				field_angle;
	t_real				beam_aperture;
	t_real				field_aperture;
}						t_light_spot;

typedef struct			s_light_dir
{
	t_real3				dir;
}						t_light_dir;

typedef union			u_light_container
{
	t_light_point		point;
	t_light_spot		spot;
	t_light_dir			dir;
}						t_light_container;

typedef struct			s_light
{
	t_light_type		type;
	cl_float3			color;
	cl_float			intensity;
	t_light_container	as;
}						t_light;

#endif
