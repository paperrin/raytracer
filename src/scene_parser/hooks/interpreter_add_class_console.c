/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_console.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 23:39:23 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 16:15:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

static int	f_class_console(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	(void)interpreter;
	(void)tk_this;
	(void)tk_return;
	if (!hook_valid_args(&args, 0))
		return (0);
	return (1);
}

static int	f_method_print(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	int		ret;

	(void)interpreter;
	(void)tk_this;
	(void)tk_return;
	if (!hook_valid_args(&args, 1,
				token_type_str | token_type_num | token_type_bool))
		return (0);
	ret = 1;
	if (args.tokens[0].type == token_type_str)
		ft_putstr(args.tokens[0].as.str.value);
	else if (args.tokens[0].type == token_type_num)
	{
		if (!(ret = ft_putfloat(args.tokens[0].as.num.value)))
			error_string(ERR_MEMORY);
	}
	else if (args.tokens[0].type == token_type_bool)
	{
		if (args.tokens[0].as.boolean.value)
			ft_putstr("true");
		else
			ft_putstr("false");
	}
	return (ret);
}

int			interpreter_add_class_console(t_interpreter *interpreter)
{
	const t_e_class_type		class_type = e_class_type_console;

	if (!(interpreter_class_add(interpreter, class_type,
					interpreter_method_create("Console", &f_class_console))))
		return (0);
	if (!(interpreter_class_add_method(interpreter, class_type,
					interpreter_method_create("print", &f_method_print))))
		return (0);
	return (1);
}
