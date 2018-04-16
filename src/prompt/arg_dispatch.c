/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:35:22 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/16 02:20:45 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "scene_parser/ast.h"
#include "scene_parser/interpreter.h"
#include "scene_parser/hooks.h"

static int		arg_device(t_app *const app, const char *argv[], int arg_index)
{
	int		ret;

	app->ocl.platform_id = 0;
	app->ocl.device_id = 42;
	if (2 == (ret = arg_devices(&app->ocl, argv[arg_index + 1])))
		return (1);
	if (ret == 1 || !ret)
		return (0);
	return (1);
}

static int		arg_scene_file(t_app *const app, const char *argv[], int arg_index)
{
	t_interpreter	*interpreter;
	t_ast			*ast;

	if (!scene_create(&app->scene))
		return (0);
	if (!scene_load(&app->scene, app))
		return (0);
	if (!(ast = ast_parse(argv[arg_index])))
		return (0);
	if (!(interpreter = interpreter_create(app)))
		return (0);
	if (!interpreter_add_class_console(interpreter))
		return (0);
	if (!interpreter_ast_eval(interpreter, ast))
		return (0);
	ast_destroy(&ast);
	interpreter_destroy(&interpreter);
	return (1);
}

int			arg_dispatch(t_app *const app, const char *argv[])
{
	int		arg_index;

	if (!argv[1])
		return (error_string("missing scene file"));
	arg_index = 1;
	if (argv[1][0] == '-' && argv[1][1] == 'd')
	{
		if (!arg_device(app, argv, arg_index))
			return (0);
		arg_index += 2;
	}
	return (arg_scene_file(app, argv, arg_index));
}
