/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 23:27:39 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 02:21:59 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

t_interpreter	*interpreter_create(t_app *app)
{
	t_interpreter	*interpreter;

	if (!(interpreter = malloc(sizeof(*interpreter))))
		return (perror_string(ERR_MEMORY));
	interpreter->app = app;
	interpreter->v_classes = interpreter_method_vector_create();
	return (interpreter);
}

void			interpreter_destroy(t_interpreter **interpreter)
{
	interpreter_method_vector_destroy(&(*interpreter)->v_classes);
	ft_memdel((void**)interpreter);
}

int			interpreter_ast_eval(t_interpreter *const interpreter,
		t_ast const *const ast)
{
	int		i;
	int		tokens_size;
	t_token	tk_result;
	t_token	*tk_expr;

	(void)interpreter;
	tokens_size = ft_vector_size(&ast->v_tokens);
	if (!ast || !tokens_size)
		return (0);
	i = -1;
	while (++i < tokens_size)
	{
		tk_expr = *(t_token**)ft_vector_at(&ast->v_tokens, i);
		if (!token_eval(interpreter, tk_expr, &tk_result))
			break ;
	}
	if (i != tokens_size)
		return (0);
	return (1);
}

t_method		*interpreter_method_find_name(
		t_interpreter *const interpreter, t_e_class_type class_type,
		char const *const name)
{
	t_method		*method;
	t_vector		*v_methods;
	int				methods_size;
	int				i;

	if (class_type != e_class_type_none)
	{
		if (!(method = interpreter_class_find_type(interpreter, class_type)))
			return (perror_string("interpreter: unknown class"));
		v_methods = &method->v_methods;
	}
	else
		v_methods = &interpreter->v_classes;
	methods_size = ft_vector_size(v_methods);
	i = -1;
	while (++i < methods_size)
	{
		method = ((t_method**)v_methods->begin)[i];
		if (!ft_strcmp(method->name, name))
			return (method);
	}
	return (perror_string("interpreter: unknown method"));
}
