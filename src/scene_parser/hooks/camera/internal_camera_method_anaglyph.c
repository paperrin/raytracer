/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_camera_method_anaglyph.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 22:52:08 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 16:12:55 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_camera_methods.h"

int			f_internal_camera_method_anaglyph(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_camera		*cam;

	(void)interpreter;
	*tk_return = *tk_this;
	cam = tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num | token_type_none))
		return (0);
	if (args.size)
		cam->cam_data.eye_offset = args.tokens[0].as.num.value;
	else
		cam->cam_data.eye_offset = ANAGLYPH_EYE_OFFSET_DEFAULT;
	if (cam->cam_data.eye_offset != 0)
		cam->cam_data.is_anaglyph = 1;
	return (1);
}

int			f_internal_camera_method_sbs(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_camera		*cam;

	(void)interpreter;
	*tk_return = *tk_this;
	cam = tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num | token_type_none))
		return (0);
	if (args.size)
		cam->cam_data.eye_offset = args.tokens[0].as.num.value;
	else
		cam->cam_data.eye_offset = SBS_EYE_OFFSET_DEFAULT;
	cam->cam_data.is_anaglyph = 0;
	return (1);
}
