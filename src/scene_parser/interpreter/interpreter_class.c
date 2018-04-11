/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_class.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:50:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 20:18:22 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

int			interpreter_class_add(t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *const class_ctor)
{
	t_method	**new_class;

	if (!class_ctor)
		return (0);
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

static int	class_add_method(t_method *const class,
		t_method *const method)
{
	t_method		**new;

	if (!(new = (t_method**)ft_vector_push_back(&class->v_methods, NULL)))
		return (error_string(ERR_MEMORY));
	*new = method;
	return (1);
}

int			interpreter_class_add_method(
		t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *const method)
{
	t_method	*class;

	if (!(class = interpreter_find_method_class_type(interpreter, class_type)))
	{
		return (error_string(
					"interpreter: failed to add method "
					"to non-existant class"));
	}
	if (interpreter_class_type_find_method_name(interpreter,
				class_type, method->name))
	{
		return (error_string(
					"interpreter: could not add method, "
					"method name already exists"));
	}
	method->class_type = class_type;
	if (!class_add_method(class, method))
		return (0);
	return (1);
}
