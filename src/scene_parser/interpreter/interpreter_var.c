/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:07:42 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 18:47:12 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

int			interpreter_var_add_is_constant(
		t_interpreter *const interpreter, char *const name, t_token value,
		int is_constant)
{
	t_interpreter_var	*new_var;

	if (interpreter_find_var_name(interpreter, name, NULL))
		return (error_string("could not add var, var already exists"));
	if (!(new_var = (t_interpreter_var*)ft_vector_push_back(
					&interpreter->v_vars, NULL)))
		return (error_string(ERR_MEMORY));
	new_var->is_constant = is_constant;
	if (!(new_var->name = ft_strdup(name)))
		return (error_string(ERR_MEMORY));
	new_var->tk_value = value;
	return (1);
}

int			interpreter_var_add(
		t_interpreter *const interpreter, char *const name, t_token value)
{
	return (interpreter_var_add_is_constant(interpreter, name, value, 0));
}

int			interpreter_constant_add(
		t_interpreter *const interpreter, char *const name, t_token value)
{
	return (interpreter_var_add_is_constant(interpreter, name, value, 1));
}

int			interpreter_find_var_name(t_interpreter *const interpreter,
		char *const name, t_interpreter_var *const r_var)
{
	t_interpreter_var	*vars;
	int					vars_size;
	int					i;

	vars = (t_interpreter_var*)interpreter->v_vars.begin;
	vars_size = ft_vector_size(&interpreter->v_vars);
	i = -1;
	while (++i < vars_size)
	{
		if (!ft_strcmp(vars[i].name, name))
		{
			if (r_var)
				*r_var = vars[i];
			return (1);
		}
	}
	return (0);
}
