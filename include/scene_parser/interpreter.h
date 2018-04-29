/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:01:28 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/28 23:33:05 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H

# include "scene_parser/ast.h"
# include "scene_parser/token.h"
# include "scene_parser/class_type.h"

typedef struct s_interpreter	t_interpreter;
typedef struct s_hook_args		t_hook_args;

typedef int			(t_f_method_hook)(
		t_interpreter *const,
		t_token *const tk_this,
		t_hook_args const args,
		t_token *const tk_return);
typedef int			(t_f_token_eval)(
		t_interpreter *const,
		t_token *const tk_this,
		t_token const *const,
		t_token *const);

typedef struct		s_method
{
	char			*name;
	t_e_class_type	class_type;
	t_f_method_hook	*f_hook;
	t_vector		v_methods;

}					t_method;

typedef struct		s_interpreter_var
{
	char			*name;
	int				is_constant;
	t_token			tk_value;
}					t_interpreter_var;

struct				s_hook_args
{
	t_token			*tokens;
	size_t			size;
	char			*hook_name;
};

struct				s_interpreter
{
	t_app			*app;
	t_vector		v_classes;
	t_vector		v_vars;
	t_vector		v_string_concats;
};

t_interpreter		*interpreter_create(t_app *app);
void				interpreter_destroy(t_interpreter **interpreter);
int					interpreter_ast_eval(t_interpreter *const interpreter,
		t_ast const *const ast);

int					token_eval(
		t_interpreter *const interpreter, t_token *const tk_this,
		t_token const *const tk_expr, t_token *const tk_result);

int					token_op_eval(
		t_interpreter *const interpreter, t_token *const tk_this,
		t_token const *const tk_expr, t_token *const tk_result);

int					token_var_eval(
		t_interpreter *const interpreter, t_token *const tk_this,
		t_token const *const tk_expr, t_token *const tk_result);

int					token_call_eval(
		t_interpreter *const interpreter, t_token *const tk_this,
		t_token const *const tk_expr, t_token *const tk_result);

t_method			*interpreter_method_create(char const *const name,
		t_f_method_hook *const f_hook);
t_vector			interpreter_method_vector_create(void);
void				interpreter_method_vector_destroy(
		t_vector *const v_methods);
void				interpreter_method_destroy(t_method *const *method);

int					interpreter_class_add(t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *const class_ctor);
int					interpreter_class_add_method(
		t_interpreter *const interpreter,
		t_e_class_type class_type, t_method *const method);
int					interpreter_class_add_method_batch(
		t_interpreter *const interpreter, t_e_class_type class_type,
		size_t const n_methods, ...);

t_method			*interpreter_find_method_class_type(
		t_interpreter const *const interpreter, t_e_class_type class_type);
t_method			*interpreter_class_type_find_method_name(
		t_interpreter *const interpreter, t_e_class_type class_type,
		char const *const name);
t_method			*interpreter_method_vector_find_method_name(
		t_vector *const v_methods, char const *const name);
t_vector			*interpreter_find_method_vector_class_type(
		t_interpreter *const interpreter, t_e_class_type class_type);

int					interpreter_var_add_is_constant(
		t_interpreter *const interpreter, char *const name, t_token value,
		int is_constant);
int					interpreter_var_add(
		t_interpreter *const interpreter, char *const name, t_token value);
int					interpreter_constant_add(
		t_interpreter *const interpreter, char *const name, t_token value);
int					interpreter_constant_add_batch(
		t_interpreter *const interpreter, size_t n_constants, ...);
t_interpreter_var	*interpreter_find_var_name(t_interpreter *const interpreter,
		char *const name);

#endif
