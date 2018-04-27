/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_camera.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 16:15:05 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 16:13:28 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_camera_methods.h"

static int	f_class_camera(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	(void)tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	scene_add_camera(&interpreter->app->scene, interpreter->app);
	tk_return->as.class.ptr = (void*)&interpreter->app->cam;
	return (1);
}

static int	f_method_fov(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_camera		*cam;
	float			fov;

	(void)interpreter;
	*tk_return = *tk_this;
	cam = (t_camera*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	fov = ft_clampf(args.tokens[0].as.num.value, 1, 180);
	cam->cam_data.fov = fov / 180.f * M_PI;
	return (1);
}

static int	f_method_pos(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_camera		*cam;

	(void)interpreter;
	*tk_return = *tk_this;
	cam = (t_camera*)tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_pos(&args, &cam->cam_data.pos));
}

static int	f_method_rot(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_camera		*cam;

	(void)interpreter;
	*tk_return = *tk_this;
	cam = (t_camera*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 3
				, token_type_num, token_type_num, token_type_num))
		return (0);
	cam->rot = vec3r(
			args.tokens[0].as.num.value / 180.f * M_PI,
			args.tokens[1].as.num.value / 180.f * M_PI,
			args.tokens[2].as.num.value / 180.f * M_PI);
	return (1);
}

int			interpreter_add_class_camera(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_camera;

	if (!interpreter_class_add(interpreter, class_type,
					interpreter_method_create("Camera", &f_class_camera)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 7,
			"fov", &f_method_fov,
			"pos", &f_method_pos,
			"rot", &f_method_rot,
			"moveSpeed", &f_internal_camera_method_move_speed,
			"rotSpeed", &f_internal_camera_method_rot_speed,
			"anaglyph", &f_internal_camera_method_anaglyph,
			"sbs", &f_internal_camera_method_sbs))
		return (0);
	return (1);
}
