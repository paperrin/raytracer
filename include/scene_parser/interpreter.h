/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:01:28 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 02:21:41 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H

# include "scene_parser/ast.h"
# include "scene_parser/token.h"

typedef struct			s_interpreter t_interpreter;

typedef int				(t_f_method_hook)(
		t_token *const tk_this,
		t_token const *const tk_args, size_t n_args,
		t_token *const tk_return);
typedef int		(t_f_token_eval)(t_interpreter *const,
		t_token const *const, t_token *const);

typedef enum			e_class_type
{
	e_class_type_none,
	e_class_type_obj_sphere,
	e_class_type_obj_plane,
	e_class_type_obj_cylinder,
	e_class_type_obj_cone,
	e_class_type_obj_cube,
	e_class_type_light_point,
	e_class_type_light_dir,
	e_class_type_light_spot,
	e_class_type_camera,
	e_class_type_material,
	e_class_type_texture
}						t_e_class_type;

typedef struct			s_method
{
	char				*name;
	t_e_class_type		class_type;
	t_f_method_hook		*f_hook;
	t_vector			v_methods;

}						t_method;

struct					s_interpreter
{
	t_app				*app;
	t_vector			v_classes;
};

t_interpreter	*interpreter_create(t_app *app);
void			interpreter_destroy(t_interpreter **interpreter);
int				interpreter_ast_eval(t_interpreter *const interpreter,
		t_ast const *const ast);

int					token_eval(t_interpreter *const interpreter,
		t_token const *const tk_expr, t_token *const tk_result);
int					token_op_eval(t_interpreter *const interpreter,
		t_token const *const tk_expr, t_token *const tk_result);
int					token_var_eval(t_interpreter *const interpreter,
		t_token const *const tk_expr, t_token *const tk_result);
int					token_call_eval(t_interpreter *const interpreter,
		t_token const *const tk_expr, t_token *const tk_result);

t_method		*interpreter_method_create(char const *const name,
		t_f_method_hook *const f_hook);
t_vector		interpreter_method_vector_create(void);
void			interpreter_method_vector_destroy(t_vector *const v_methods);
void			interpreter_method_destroy(t_method *const *method);

int				interpreter_class_add(t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *class_ctor);
int				interpreter_class_add_method(t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *method);

t_method		*interpreter_method_find_name(
		t_interpreter *const interpreter, t_e_class_type class_type,
		char const *const name);
t_method		*interpreter_class_find_type(
		t_interpreter const *const interpreter, t_e_class_type class_type);

#endif
