/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_class.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:50:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 11:47:58 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

int			interpreter_class_add(t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *const class_ctor)
{
	t_method	**new_class;

	if (!class_ctor)
		return (error_string("could not add class with null constructor"));
	if (interpreter_find_method_class_type(interpreter, class_type))
	{
		return (error_string(
					"interpreter: could not add class, "
					"class already exists"));
	}
	if (!(new_class = (t_method**)ft_vector_push_back(
					&interpreter->v_classes, NULL)))
		return (error_string(ERR_MEMORY));
	class_ctor->class_type = class_type;
	*new_class = class_ctor;
	return (1);
}

static int	method_vector_add_method(t_vector *const v_methods,
		t_method *const method)
{
	t_method		**new_method;

	if (!(new_method = (t_method**)ft_vector_push_back(v_methods, NULL)))
		return (error_string(ERR_MEMORY));
	*new_method = method;
	return (1);
}

int			interpreter_class_add_method(
		t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *const method)
{
	t_vector	*v_methods;

	if (!(v_methods = interpreter_find_method_vector_class_type(
					interpreter, class_type)))
	{
		return (error_string_2(
					"interpreter: failed to add method "
					"to non-existant class", method->name));
	}
	if (interpreter_method_vector_find_method_name(v_methods, method->name))
	{
		return (error_string_2(
					"interpreter: could not add method, "
					"method name already exists", method->name));
	}
	method->class_type = class_type;
	if (!method_vector_add_method(v_methods, method))
		return (0);
	return (1);
}

int			interpreter_class_add_method_batch(t_interpreter *const interpreter
		, t_e_class_type class_type, size_t const n_methods, ...)
{
	char				*method_name;
	t_f_method_hook		*f_method_hook;
	int					i;

	va_list(ap);
	va_start(ap, n_methods);
	i = -1;
	while (++i < (int)n_methods)
	{
		method_name = va_arg(ap, char*);
		f_method_hook = va_arg(ap, t_f_method_hook*);
		if (!method_name || !f_method_hook)
			break ;
		if (!interpreter_class_add_method(interpreter, class_type,
					interpreter_method_create(method_name, f_method_hook)))
			break ;
	}
	va_end(ap);
	if (i != (int)n_methods)
		return (0);
	return (1);
}
