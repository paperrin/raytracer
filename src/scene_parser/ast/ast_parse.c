/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:21:37 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 20:03:10 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/ast.h"

static int			parse_program(t_ast *const ast,
		t_token_stream *const tkstream)
{
	t_token		*tk_new;
	t_token		**token;

	ast->v_tokens = ft_vector_create(sizeof(t_token*), NULL, NULL);
	while (cstream_peek(tkstream->cstream) > -1)
	{
		if (!(tk_new = ast_parse_expr(tkstream)) || tkstream->did_error)
		{
			if (cstream_peek(tkstream->cstream) < -1)
				return (tkstream_ferror(tkstream, "read error"));
			return (!tkstream->did_error);
		}
		if (tk_new->type != token_type_op && tk_new->type != token_type_call)
			return (tkstream_error(tkstream, "unexpected instruction"));
		if (!(token = (t_token**)ft_vector_push_back(&ast->v_tokens, NULL)))
			return (tkstream_error(tkstream, ERR_MEMORY));
		*token = tk_new;
	}
	return (1);
}

t_ast				*ast_parse(char const *const file_path)
{
	t_token_stream		*tkstream;
	t_ast				*ast;

	if (!(tkstream = tkstream_open(file_path)))
		return (NULL);
	if ((ast = (t_ast*)malloc(sizeof(*ast))))
	{
		if (!parse_program(ast, tkstream))
		{
			ast_destroy(&ast);
			return (perror_string("AST parsing failed"));
		}
	}
	else
		error_string(ERR_MEMORY);
	tkstream_close(&tkstream);
	return (ast);
}

void				ast_print(t_ast const *const ast)
{
	int		i;
	int		size;

	ft_putendl("{");
	size = (int)ft_vector_size(&ast->v_tokens);
	i = -1;
	while (++i < size)
	{
		token_print(((t_token**)ast->v_tokens.begin)[i], 1);
		ft_putendl((i < size - 1) ? "," : "");
	}
	ft_putendl("}");
}

void				ast_destroy(t_ast **ast)
{
	int			i;

	if (!ast)
		return ;
	if (*ast)
	{
		i = -1;
		while (++i < (int)ft_vector_size(&(*ast)->v_tokens))
			token_destroy(&((t_token**)(*ast)->v_tokens.begin)[i]);
		ft_vector_destroy(&(*ast)->v_tokens);
		ft_memdel((void**)ast);
	}
}
