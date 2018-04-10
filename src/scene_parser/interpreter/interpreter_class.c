/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_class.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:50:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 02:06:01 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

int					interpreter_class_add(t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *class_ctor)
{
	t_method	**new_class;

	if (!class_ctor)
		return (0);
	if (!(new_class = (t_method**)ft_vector_push_back(
					&interpreter->v_classes, NULL)))
		return (error_string(ERR_MEMORY));
	class_ctor->class_type = class_type;
	*new_class = class_ctor;
	return (1);
}

static int			class_add_method(t_method *class, t_method *method)
{
	t_method		**new;

	if (!(new = (t_method**)ft_vector_push_back(&class->v_methods, NULL)))
		return (error_string(ERR_MEMORY));
	*new = method;
	return (1);
}

t_method			*interpreter_class_find_type(
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

int					interpreter_class_add_method(t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *method)
{
	t_method	*class;

	if (!(class = interpreter_class_find_type(interpreter, class_type)))
		return (error_string(
				"interpreter: failed to add method to non-existant class"));
	if (!class_add_method(class, method))
		return (0);
	return (1);
}
