/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 17:08:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 23:56:27 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "rt.h"
# include "scene_parser/class_type.h"

# define TOKEN_READ_NB_F_TOKENS 5
# define TOKEN_PRINT_NB_F_TOKENS 6
# define TOKEN_DESTROY_NB_F_TOKENS 6
# define TOKEN_EVAL_NB_F_TOKENS 3
# define TOKEN_DUP_NB_F_TOKENS 6

typedef enum				e_token_type
{
	token_type_punc,
	token_type_num,
	token_type_str,
	token_type_var,
	token_type_op,
	token_type_call,
	token_type_class
}							t_e_token_type;

typedef struct s_token			t_token;

typedef int		(t_f_token_print)(t_token const *const, unsigned int);
typedef void	(t_f_token_destroy)(t_token*);
typedef void	(t_f_token_ptr_destroy)(void**);

typedef struct				s_token_var
{
	char					*name;
}							t_token_var;

typedef struct				s_token_call
{
	char					*func;
	t_token					**args;
	int						args_len;
}							t_token_call;

typedef struct				s_token_punc
{
	char					value;
}							t_token_punc;

typedef struct				s_token_num
{
	float					value;
}							t_token_num;

typedef struct				s_token_str
{
	char					*value;
}							t_token_str;

typedef struct				s_token_op
{
	char					value;
	t_token					*left;
	t_token					*right;
}							t_token_op;

typedef struct				s_token_class
{
	t_e_class_type			class_type;
	void					*ptr;
}							t_token_class;

typedef union				u_token_container
{
	t_token_call			call;
	t_token_punc			punc;
	t_token_num				num;
	t_token_str				str;
	t_token_var				var;
	t_token_op				op;
	t_token_class			class;
}							t_u_token_container;

struct						s_token
{
	t_e_token_type		type;
	t_u_token_container	as;
};

int					token_print(t_token const *const token,
		unsigned int indent_depth);
int					token_punc_print(t_token const *const token,
		unsigned int indent_depth);
int					token_op_print(t_token const *const token,
		unsigned int indent_depth);
int					token_str_print(t_token const *const token,
		unsigned int indent_depth);
int					token_num_print(t_token const *const token,
		unsigned int indent_depth);
int					token_var_print(t_token const *const token,
		unsigned int indent_depth);
int					token_call_print(t_token const *const token,
		unsigned int indent_depth);
void				token_indent(unsigned int indent_depth);

void				token_destroy(t_token **token);
void				token_content_destroy(t_token *const token);
/* TODO: Change below prototypes params to *const token */
void				token_punc_destroy(t_token *token);
void				token_num_destroy(t_token *token);
void				token_str_destroy(t_token *token);
void				token_var_destroy(t_token *token);
void				token_op_destroy(t_token *token);
void				token_call_destroy(t_token *token);

t_token				*token_num(float value);

#endif
