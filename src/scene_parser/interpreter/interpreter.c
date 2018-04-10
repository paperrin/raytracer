/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 23:27:39 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 16:46:40 by paperrin         ###   ########.fr       */
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
	t_token	tk_this;
	t_token	*tk_expr;
	t_token	tk_result;

	tokens_size = ft_vector_size(&ast->v_tokens);
	if (!ast || !tokens_size)
		return (0);
	i = -1;
	while (++i < tokens_size)
	{
		tk_this.as.class.class_type = e_class_type_none;
		tk_this.as.class.ptr = NULL;
		tk_expr = *(t_token**)ft_vector_at(&ast->v_tokens, i);
		if (!token_eval(interpreter, &tk_this, tk_expr, &tk_result))
			break ;
	}
	if (i != tokens_size)
		return (0);
	return (1);
}
