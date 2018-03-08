/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:36:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/17 21:40:42 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "opencl.h"
# include "window.h"
# include "ft_vector.h"
# include "shared.h"
# include "vec.h"
# include "image.h"
# include "camera.h"

# define APP_WIDTH 720
# define APP_HEIGHT 480
# define APP_TITLE "R-T RT"

typedef struct		s_scene
{
	t_vector		v_material;
	t_vector		v_obj;
	t_vector		v_light;
	t_vector		v_texture;
	cl_uchar		*texture_pixels;
	cl_ulong		n_texture_pixels;
}					t_scene;

typedef struct		s_app
{
	t_window		win;
	t_scene			scene;
	t_camera		cam;
	t_image			draw_buf;
	t_opencl		ocl;
	t_ocl_kernel	kernel_ray_gen;
	t_ocl_kernel	kernel_ray_trace;
	t_ocl_kernel	kernel_clear;
	t_ocl_kernel	kernel_ray_shade;
	t_ocl_kernel	kernel_prefix_sum;
	t_ocl_kernel	kernel_ray_sort;
	cl_uint			n_hits;
	cl_uint			n_rays;
	int				should_sort_rays;
	char			mouse_captured;
	t_config		config;
}					t_app;

int					app_create(t_app *app);
void				app_destroy(t_app *app, int exit_status);

void				callback_key(void *user_ptr, int key, int action);
void				callback_mouse_motion(void *user_ptr, double x, double y);
void				process_input(t_app *app, double elapsed);

int					error_cl_code(cl_int err_code);
void				*perror_cl_code(cl_int err_code);
int					error_string(char const *const error_str);

t_obj				obj_sphere(t_real3 pos, t_real radius, t_mat_id material);
t_obj				obj_plane(t_real3 pos, t_real3 normal, t_real3 up, t_mat_id material);

void				render(void *user_ptr, double elapsed);


int					kernel_ray_gen_primary_create(t_app *app);
int					kernel_ray_gen_primary_launch(t_app *app);
void				kernel_ray_gen_primary_destroy(t_app *app);

int					kernel_ray_trace_create(t_app *app);
int					kernel_ray_trace_launch(t_app *app);
void				kernel_ray_trace_destroy(t_app *app);

int					kernel_ray_shade_create(t_app *app);
int					kernel_ray_shade_launch(t_app *app);
void				kernel_ray_shade_destroy(t_app *app);

int					kernel_clear_create(t_app *app);
int					kernel_clear_launch(t_app *app);
void				kernel_clear_destroy(t_app *app);

int					kernel_prefix_sum_create(t_app *app);
int					kernel_prefix_sum_launch(t_app *app);
void				kernel_prefix_sum_destroy(t_app *app);

int					kernel_ray_sort_create(t_app *app);
int					kernel_ray_sort_launch(t_app *app);
void				kernel_ray_sort_destroy(t_app *app);
#endif
