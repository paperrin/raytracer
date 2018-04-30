/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 23:27:39 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/29 00:14:31 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

static void		f_var_destroy(void *buff)
{
	t_interpreter_var	*var;

	var = (t_interpreter_var*)buff;
	ft_strdel(&var->name);
	token_content_destroy(&var->tk_value);
}

static void		f_str_concat_destroy(void *buff)
{
	char		**s;

	s = (char**)buff;
	ft_strdel(s);
}

t_interpreter	*interpreter_create(t_app *app)
{
	t_interpreter	*interpreter;

	if (!(interpreter = malloc(sizeof(*interpreter))))
		return (perror_string(ERR_MEMORY));
	interpreter->app = app;
	interpreter->v_classes = interpreter_method_vector_create();
	interpreter->v_vars = ft_vector_create(sizeof(t_interpreter_var),
			NULL, &f_var_destroy);
	interpreter->v_string_concats = ft_vector_create(sizeof(char*),
			NULL, &f_str_concat_destroy);
	if (!interpreter_constant_add(interpreter, "true", token_bool(1)))
		interpreter_destroy(&interpreter);
	if (!interpreter_constant_add(interpreter, "false", token_bool(0)))
		interpreter_destroy(&interpreter);
	return (interpreter);
}

void			interpreter_destroy(t_interpreter **interpreter)
{
	interpreter_method_vector_destroy(&(*interpreter)->v_classes);
	ft_vector_destroy(&(*interpreter)->v_vars);
	ft_vector_destroy(&(*interpreter)->v_string_concats);
	ft_memdel((void**)interpreter);
}

int				interpreter_ast_eval(t_interpreter *const interpreter,
		t_ast const *const ast)
{
	int		i;
	int		tokens_size;
	t_token	tk_this;
	t_token	*tk_expr;
	t_token	tk_result;

	tokens_size = ft_vector_size(&ast->v_tokens);
	if (!ast || !tokens_size)
		return (0);
	i = -1;
	while (++i < tokens_size)
	{
		tk_this = token_class(e_class_type_none, NULL);
		tk_expr = *(t_token**)ft_vector_at(&ast->v_tokens, i);
		if (!token_eval(interpreter, &tk_this, tk_expr, &tk_result))
			break ;
	}
	if (i != tokens_size)
		return (0);
	return (1);
}
