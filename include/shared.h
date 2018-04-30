/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:25:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 22:43:47 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

/*
** Please care of data packing when changing data types / structure order
*/

# include "t_real.h"

# ifdef CONFIG_USE_DOUBLE
#  ifdef cl_khr_fp64
#   pragma OPENCL EXTENSION cl_khr_fp64 : enable
#   define DOUBLE_SUPPORT_AVAILABLE
#  elif defined cl_amd_fp64
#   pragma OPENCL EXTENSION cl_amd_fp64 : enable
#   define DOUBLE_SUPPORT_AVAILABLE
#  endif
# endif

typedef cl_short		t_obj_type;
typedef cl_int			t_obj_id;
typedef cl_int			t_mat_id;

typedef	struct s_material	t_material;
typedef	struct s_ray		t_ray;

typedef struct			s_camera_data
{
	t_real3				pos;
	t_real3				dir;
	t_real3				up;
	t_real3				right;
	t_real				fov;
	t_real				eye_offset;
	int					is_anaglyph;
}						t_camera_data;

typedef cl_float3	(t_f_specular_model)(t_material, t_real3, t_ray, t_real3
		, t_real3, cl_float3);

typedef enum			e_shading_model
{
	e_shading_model_phong = 0,
	e_shading_model_blinn
}						t_e_shading_model;

typedef enum			e_post_filter
{
	e_post_filter_none = 0,
	e_post_filter_sepia = 1 << 0,
	e_post_filter_grayscale = 1 << 1
}						t_e_post_filter;

typedef struct			s_config
{
	cl_float3			ambient_c;
	cl_float			ambient_i;
	cl_float3			camera_light_c;
	cl_float			camera_light_i;
	cl_float			color_epsilon;
	cl_uint				projection_depth;
	t_real				intersection_bias;
	t_real				z_far;
	cl_uint				samples_width;
	t_e_shading_model	shading_model;
	cl_uint2			screen_size;
	cl_int				max_depth;
	cl_int				cur_depth;
	cl_int				mouse_pxl_id;
	cl_uint				post_filters;
	cl_uint				fxaa;
	cl_float3			anaglyph_r[2];
	cl_float3			anaglyph_g[2];
	cl_float3			anaglyph_b[2];
}						t_config;

/*
** Rays
*/

struct					s_ray
{
	t_real3				origin;
	t_real3				dir;
};

typedef struct			s_ray_state
{
	t_ray				ray;
	t_real				t;
	cl_float			importance;
	cl_uint				pxl_id;
	t_obj_id			obj_id;
	cl_float3			color_factor;
}						t_ray_state;

/*
** Objects
*/

typedef enum			e_obj_type
{
	e_type_sphere,
	e_type_plane,
	e_type_cylinder,
	e_type_cone,
	e_type_aligned_cube
}						t_e_obj_type;

typedef struct			s_sphere
{
	t_real				radius;
}						t_sphere;

typedef struct			s_cylinder
{
	t_real				radius;
	t_real				caps[2];
}						t_cylinder;

typedef struct			s_cone
{
	t_real				angle;
}						t_cone;

typedef	struct			s_aligned_cube
{
	t_real3				size;
}						t_aligned_cube;

typedef union			u_obj_container
{
	t_sphere			sphere;
	t_cylinder			cylinder;
	t_cone				cone;
	t_aligned_cube		aligned_cube;
}						t_obj_container;

typedef struct			s_obj
{
	t_mat_id			material_id;
	t_obj_type			type;
	t_real3				pos;
	t_real3				up;
	t_real3				normal;
	t_obj_container		as;
}						t_obj;

struct					s_material
{
	cl_float3			color;
	cl_float			reflection;
	cl_float			refraction;
	cl_float			emission;
	cl_int				ignores_light;
	cl_float			specular;
	cl_float3			specular_color;
	cl_float			specular_exp;
	cl_float			refraction_index;
	cl_uint				projection;
	cl_int				texture_id;
	cl_int				refraction_map_id;
};

typedef enum			e_filter
{
	e_filter_nearest = 0,
	e_filter_bilinear
}						t_filter;

typedef	struct			s_texture_image
{
	cl_long				pixels_offset;
	cl_uint				width;
	cl_uint				height;
	cl_uint				max_val;
	t_filter			filter;
}						t_texture_image;

typedef struct			s_texture_checkerboard
{
	cl_float3			color1;
	cl_float3			color2;
}						t_texture_checkerboard;

typedef struct			s_texture_sine
{
	cl_float3			color1;
	cl_float3			color2;
	cl_float3			color3;
	cl_float3			color4;
	t_real2				factors;
}						t_texture_sine;

typedef struct			s_texture_noise
{
	cl_float3			color1;
	cl_float3			color2;
}						t_texture_noise;

typedef union			u_texture_origin
{
	t_texture_image			image;
	t_texture_checkerboard	checkerboard;
	t_texture_sine			sine;
	t_texture_noise			noise;
}						t_u_texture_origin;

typedef	enum			e_texture_type
{
	e_texture_type_image,
	e_texture_type_checkerboard,
	e_texture_type_sine,
	e_texture_type_noise
}						t_e_texture_type;

typedef struct			s_texture
{
	t_e_texture_type	type;
	t_u_texture_origin	as;
	t_real2				translate;
	t_real2				scale;
}						t_texture;

/*
** Lights
*/

typedef enum			e_light_type
{
	e_light_type_point,
	e_light_type_spot,
	e_light_type_dir
}						t_light_type;

typedef struct			s_light_point
{
	t_real3				pos;
}						t_light_point;

typedef struct			s_light_spot
{
	t_real3				pos;
	t_real3				dir;
	t_real				beam_aperture;
	t_real				beam_gradient;
	t_real				field_aperture;
	t_real				field_intensity;
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
	cl_float			glare;
	cl_float			dispersion;
	t_light_container	as;
}						t_light;

/*
** Anti-aliasing
*/

typedef struct			s_directions
{
	cl_float			north;
	cl_float			south;
	cl_float			east;
	cl_float			west;
}						t_directions;

typedef struct			s_edge
{
	cl_float2			uv;
	cl_float			luma;
}						t_edge;

typedef struct			s_anti_aliasing
{
	cl_float			center;
	t_directions		orig;
	t_directions		corners;
	cl_float			x_axis;
	cl_float			y_axis;
	cl_float			range;
	cl_int				is_horizontal;
	t_edge				end_one;
	t_edge				end_two;
	cl_float			gradscaled;
	cl_float			final_offset;
	cl_float			local_average;
	cl_float			step_length;
}						t_anti_aliasing;

#endif
