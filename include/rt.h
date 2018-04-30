/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:36:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 23:40:51 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "opencl.h"
# include "window.h"
# include "ft_vector.h"
# include "ft_map.h"
# include "shared.h"
# include "vec.h"
# include "image.h"
# include "camera.h"
# include "error.h"
# include "ft_math.h"
# include "ppm.h"

# define APP_WIDTH 720
# define APP_HEIGHT 480
# define APP_TITLE "R-T RT"
# define APP_SCREENSHOT_PATH "./Screen Shot "
# define APP_USAGE "usage: ./rt [-d [platform_id:device_id]] <file.rt>\n"

# define ANAGLYPH_EYE_OFFSET_DEFAULT 0.5
# define SBS_EYE_OFFSET_DEFAULT 0.5

typedef struct		s_scene
{
	t_matrix		mx;
	t_matrix		mx_r;
	t_vector		v_mx;
	t_vector		v_mx_r;
	t_map			m_material;
	t_map			m_obj;
	t_map			m_light;
	t_map			m_texture;
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
	t_ocl_kernel	kernel_post_process;
	cl_uint			n_hits;
	cl_uint			n_rays;
	char			mouse_captured;
	t_config		config;
}					t_app;

int					scene_create(t_scene *const scene);
void				scene_destroy(t_scene *const scene);
int					scene_load(t_scene *const scene, t_app *const app);

t_map				scene_map_create(size_t val_size);
void				*scene_map_search(t_map const *const map,
		char const *const name);
int					scene_map_search_index(t_map const *const map,
		char const *const name);
void				*scene_map_add(t_map *const map,
		char const *const name);

t_obj				*scene_add_sphere(
		t_scene *const scene, char const *const name);
t_obj				*scene_add_plane(
		t_scene *const scene, char const *const name);
t_obj				*scene_add_cylinder(
		t_scene *const scene, char const *const name);
t_obj				*scene_add_cone(
		t_scene *const scene, char const *const name);
t_obj				*scene_add_aligned_cube(
		t_scene *const scene, char const *const name);
t_material			*scene_add_material(
		t_scene *const scene, char const *const name);
t_light				*scene_add_dir_light(
		t_scene *const scene, char const *const name);
t_light				*scene_add_spot_light(
		t_scene *const scene, char const *const name);
t_light				*scene_add_point_light(
		t_scene *const scene, char const *const name);
t_texture			*scene_add_texture(
		t_scene *const scene, char const *const name, char const *const path);
int					scene_add_default_texture(t_scene *const scene);
t_texture			*scene_add_texture_wave(
		t_scene *const scene, char const *const name);
t_texture			*scene_add_texture_checkerboard(
		t_scene *const scene, char const *const name);
t_texture			*scene_add_texture_noise(t_scene *const scene,
		char const *const name);
void				scene_add_camera(
		t_scene *const scene, t_app *const app);
void				scene_camera_translate(
		t_camera *const cam, double x, double y, double z);
void				scene_camera_update(t_camera *const cam);

void				scene_rotate(
		t_scene *const scene, float x, float y, float z);
void				scene_translate(
		t_scene *const scene, float x, float y, float z);
void				scene_transform(
		t_real3 *const vec3r, t_matrix const *const mx);
void				scene_transform_pos(
		t_scene const *const scene, t_real3 *const vec3r);
void				scene_transform_dir(
		t_scene const *const scene, t_real3 *const vec3r);
int					scene_transform_push(t_scene *const scene);
void				scene_transform_pop(t_scene *const scene);

int					app_create(t_app *app, int ac, const char *argv[]);
void				app_destroy(t_app *app, int exit_status);

int					arg_dispatch(t_app *const app, int ac, const char *argv[]);
int					arg_devices(t_opencl *ocl, const char *args);

void				callback_key(void *user_ptr, int key, int action);
void				process_input(t_app *app, double elapsed);

void				render(void *user_ptr, double elapsed);

int					update_gpu_config(t_app *app);

int					kernel_ray_gen_primary_create(t_app *app);
int					kernel_ray_gen_primary_launch(t_app *app);
void				kernel_ray_gen_primary_destroy(t_app *app);

int					kernel_ray_trace_create(t_app *app);
int					kernel_ray_trace_launch(t_app *app);
void				kernel_ray_trace_destroy(t_app *app);

int					kernel_ray_shade_create(t_app *app);
int					kernel_ray_shade_args(t_app *app);
int					kernel_ray_shade_launch(t_app *app);
void				kernel_ray_shade_destroy(t_app *app);

int					kernel_clear_create(t_app *app);
int					kernel_clear_launch(t_app *app);
void				kernel_clear_destroy(t_app *app);

int					kernel_post_process_create(t_app *app);
int					kernel_post_process_launch(t_app *app);
void				kernel_post_process_destroy(t_app *app);

char				*get_unique_file_name(const char *path, const char *ext);
int					save_screenshot(t_app *app);

#endif
