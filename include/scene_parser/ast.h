/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:26:00 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 20:19:46 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "rt.h"
# include "scene_parser/token.h"
# include "scene_parser/tkstream.h"

# define OPERATOR_PRECEDENCE_NB_OPS 5

typedef struct			s_ast
{
	t_vector			v_tokens;
}						t_ast;

t_ast					*ast_parse(char const *const file_path);
t_token					*ast_parse_expr(t_token_stream *const tkstream);
t_token					*ast_parse_maybe_call(t_token_stream *const tkstream);

void					ast_print(t_ast const *const ast);
int						ast_eval(t_ast const *const ast, t_app *const app);

void					ast_destroy(t_ast **ast);

void					*ast_error(t_token_stream *const tkstream,
		char const *const err_str);

#endif
