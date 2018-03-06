/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 15:51:44 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/13 17:35:40 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_PARSER_H
# define SCENE_PARSER_H

# include "ft_fstream.h"
# include "ft_printf.h"
# include "rt.h"

# define TKSTREAM_NB_F_TOKENS 5
# define TOKEN_DESTROY_NB_F_TOKENS 8

typedef enum		e_token_type
{
	token_type_punc,
	token_type_num,
	token_type_str,
	token_type_kw,
	token_type_var,
	token_type_op,
	token_type_call,
	token_type_bool
}					t_e_token_type;

typedef struct s_token			t_token;

typedef struct s_token_stream	t_token_stream;

typedef t_token *(t_f_token_read)(t_token_stream *const);
typedef void	(t_f_token_print)(t_token const *const);
typedef void	(t_f_token_destroy)(t_token*);

typedef struct		s_token_var
{
	char			*name;
}					t_token_var;

typedef struct		s_token_call
{
	char			*func;
	t_token			*args;
	int				args_len;
}					t_token_call;

typedef struct		s_token_punc
{
	char			value;
}					t_token_punc;

typedef struct		s_token_num
{
	float			value;
}					t_token_num;

typedef struct		s_token_str
{
	char			*value;
}					t_token_str;

typedef struct		s_token_bool
{
	int				value;
}					t_token_bool;

typedef struct		s_token_kw
{
	char			*value;
}					t_token_kw;

typedef struct		s_token_op
{
	char			value;
}					t_token_op;

typedef union		u_token_container
{
	t_token_call	call;
	t_token_punc	punc;
	t_token_num		num;
	t_token_str		str;
	t_token_bool	boo;
	t_token_var		var;
	t_token_kw		kw;
	t_token_op		op;
}					t_u_token_container;

struct				s_token
{
	t_e_token_type		type;
	t_u_token_container	as;
};

typedef struct		s_char_stream
{
	char			*file_path;
	t_fstream		*fstream;
	unsigned int	line;
	unsigned int	col;
}					t_char_stream;

struct				s_token_stream
{
	t_token			*cur;
	t_char_stream	*cstream;
	unsigned int	line;
	unsigned int	col;
};

typedef struct		s_ast
{
	t_token			**tokens;
}					t_ast;

t_char_stream		*cstream_open(char const *const file_path);
void				cstream_close(t_char_stream **cstream);
char				cstream_next(t_char_stream *const cstream);
char				cstream_peek(t_char_stream *const cstream);
int					cstream_error(t_char_stream const *const cstream,
		char const *const error);
void				cstream_skip_chars(t_char_stream *const cstream,
		char const *const chars);
void				cstream_skip_to_chars(t_char_stream *const cstream,
		char const *const chars);
void				cstream_skip_whitespaces(t_char_stream *const cstream);

t_token_stream		*tkstream_open(char const *const file_path);
void				tkstream_close(t_token_stream **tkstream);
t_token				*tkstream_next(t_token_stream *const tkstream);
t_token				*tkstream_peek(t_token_stream *const tkstream);
int					tkstream_error(t_token_stream const *const tkstream,
		char const *const error);
t_token				*tkstream_read_token(t_token_stream *const tkstream);
t_token				*tkstream_read_punc(t_token_stream *const tkstream);
t_token				*tkstream_read_op(t_token_stream *const tkstream);
t_token				*tkstream_read_str(t_token_stream *const tkstream);
t_token				*tkstream_read_num(t_token_stream *const tkstream);
t_token				*tkstream_read_var(t_token_stream *const tkstream);
void				tkstream_print_token(t_token const *const token);
void				tkstream_print_punc(t_token const *const token);
void				tkstream_print_op(t_token const *const token);
void				tkstream_print_str(t_token const *const token);
void				tkstream_print_num(t_token const *const token);
void				tkstream_print_var(t_token const *const token);

void				token_destroy(t_token **token);
void				token_punc_destroy(t_token *token);
void				token_num_destroy(t_token *token);
void				token_str_destroy(t_token *token);
void				token_kw_destroy(t_token *token);
void				token_var_destroy(t_token *token);
void				token_op_destroy(t_token *token);
void				token_call_destroy(t_token *token);
void				token_bool_destroy(t_token *token);

t_ast				*ast_parse(char const *const file_path);
void				ast_destroy(t_ast **ast);

#endif
