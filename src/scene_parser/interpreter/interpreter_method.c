/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_method.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 22:44:19 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/22 19:52:23 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

static void		f_method_destroy(void *buff)
{
	t_method		**method;

	method = (t_method**)buff;
	interpreter_method_destroy(method);
}

t_method		*interpreter_method_create(char const *const name,
		t_f_method_hook *const f_hook)
{
	t_method		*method;

	if (!name)
		return (perror_string("method name can't be null"));
	if (!(method = malloc(sizeof(*method))))
		return (perror_string(ERR_MEMORY));
	if (!(method->name = ft_strdup(name)))
	{
		ft_memdel((void**)&method);
		return (perror_string(ERR_MEMORY));
	}
	method->class_type = e_class_type_none;
	method->f_hook = f_hook;
	method->v_methods = interpreter_method_vector_create();
	return (method);
}

t_vector		interpreter_method_vector_create(void)
{
	t_vector		v_methods;

	v_methods = ft_vector_create(sizeof(t_method*), NULL, &f_method_destroy);
	return (v_methods);
}

void			interpreter_method_vector_destroy(t_vector *const v_methods)
{
	ft_vector_destroy(v_methods);
}

void			interpreter_method_destroy(t_method *const *method)
{
	interpreter_method_vector_destroy(&(*method)->v_methods);
	ft_memdel((void**)&(*method)->name);
	ft_memdel((void**)method);
}
