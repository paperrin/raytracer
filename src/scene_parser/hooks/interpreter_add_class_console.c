/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_console.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 23:39:23 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 23:42:20 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

static int	f_class_console(t_token *const tk_this,
		t_token const *const tk_args, size_t n_args, t_token *const tk_return)
{
	(void)tk_this;
	(void)tk_return;
	(void)tk_args;
	if (n_args)
		return (error_string("Too many arguments: Console()"));
	tk_return->as.class.class_type = e_class_type_console;
	return (1);
}

static int	f_method_print(t_token *const tk_this,
		t_token const *const tk_args, size_t n_args, t_token *const tk_return)
{
	if (!n_args || tk_args[0].type != token_type_str)
		return (error_string("Wrong argument: print(string)"));
	ft_putendl(tk_args[0].as.str.value);
	*tk_return = *tk_this;
	return (1);
}

int			interpreter_add_class_console(t_interpreter *interpreter)
{
	if (!(interpreter_class_add(interpreter, e_class_type_console,
					interpreter_method_create("Console", &f_class_console))))
		return (error_string("could not add class"));
	if (!(interpreter_class_add_method(interpreter, e_class_type_console,
					interpreter_method_create("print", &f_method_print))))
		return (error_string("could not add method"));
	return (1);
}
