/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_find_method.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:36:52 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 15:17:02 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

t_method			*interpreter_method_vector_find_method_name(
		t_vector *const v_methods, char const *const name)
{
	t_method		*method;
	int				methods_size;
	int				i;

	methods_size = ft_vector_size(v_methods);
	i = -1;
	while (++i < methods_size)
	{
		method = ((t_method**)v_methods->begin)[i];
		if (!ft_strcmp(method->name, name))
			return (method);
	}
	return (NULL);
}

t_vector			*interpreter_find_method_vector_class_type(
		t_interpreter *const interpreter, t_e_class_type class_type)
{
	t_method		*method;

	if (class_type != e_class_type_none)
	{
		if (!(method = interpreter_find_method_class_type(
						interpreter, class_type)))
			return (NULL);
		return (&method->v_methods);
	}
	return (&interpreter->v_classes);
}

t_method			*interpreter_find_method_class_type(
		t_interpreter const *const interpreter, t_e_class_type class_type)
{
	t_method	*cur_class;
	int			classes_size;
	int			i;

	classes_size = ft_vector_size(&interpreter->v_classes);
	i = -1;
	while (++i < classes_size)
	{
		cur_class = ((t_method**)interpreter->v_classes.begin)[i];
		if (cur_class->class_type == class_type)
			return (cur_class);
	}
	return (NULL);
}

t_method			*interpreter_class_type_find_method_name(
		t_interpreter *const interpreter, t_e_class_type class_type,
		char const *const name)
{
	t_method		*method;
	t_vector		*v_methods;

	if (!(v_methods = interpreter_find_method_vector_class_type(
					interpreter, class_type)))
		return (NULL);
	if (!(method = interpreter_method_vector_find_method_name(v_methods, name)))
		return (NULL);
	return (method);
}
