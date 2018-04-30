/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:23:26 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/28 21:41:56 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "vec.h"

static t_camera		camera_default(void)
{
	t_camera		camera;

	camera.rot = vec3r(0, 0, 0);
	camera.cam_data.dir = vec3r(0, 0, 1);
	camera.cam_data.up = vec3r(0, 1, 0);
	camera.cam_data.right = vec3r(1, 0, 0);
	camera.cam_data.pos = vec3r(0, 0, 0);
	camera.cam_data.fov = M_PI / 2;
	camera.cam_data.eye_offset = 0;
	camera.cam_data.is_anaglyph = 0;
	camera.move_speed = 0.5;
	camera.rot_speed = 3;
	return (camera);
}

void				scene_add_camera(t_scene *const scene, t_app *const app)
{
	(void)scene;
	app->cam = camera_default();
}

void				scene_camera_translate(t_camera *const cam,
		double x, double y, double z)
{
	cam->cam_data.pos.s[0] += cam->cam_data.right.s[0] * x;
	cam->cam_data.pos.s[1] += cam->cam_data.right.s[1] * x;
	cam->cam_data.pos.s[2] += cam->cam_data.right.s[2] * x;
	cam->cam_data.pos.s[0] += cam->cam_data.up.s[0] * y;
	cam->cam_data.pos.s[1] += cam->cam_data.up.s[1] * y;
	cam->cam_data.pos.s[2] += cam->cam_data.up.s[2] * y;
	cam->cam_data.pos.s[0] += cam->cam_data.dir.s[0] * z;
	cam->cam_data.pos.s[1] += cam->cam_data.dir.s[1] * z;
	cam->cam_data.pos.s[2] += cam->cam_data.dir.s[2] * z;
}

void				scene_camera_update(t_camera *const cam)
{
	t_real16	mat;

	matrix_real16_id(&mat);
	matrix_real16_rot_x(&mat, cam->rot.s[0]);
	matrix_real16_rot_y(&mat, cam->rot.s[1]);
	matrix_real16_rot_z(&mat, cam->rot.s[2]);
	cam->cam_data.dir = matrix_real3_rot(&mat, vec3r(0, 0, 1));
	cam->cam_data.up = matrix_real3_rot(&mat, vec3r(0, 1, 0));
	cam->cam_data.right = matrix_real3_rot(&mat, vec3r(1, 0, 0));
}
