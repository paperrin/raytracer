/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:21:37 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/17 15:22:23 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"
#include <stdio.h>

static int			parse_program(t_ast *const ast,
		t_token_stream *const tkstream)
{
	t_vector	v_tokens;
	t_token		**token;

	if (!(token = (t_token**)malloc(sizeof(t_token*))))
		return (0);
	v_tokens = ft_vector_create(sizeof(t_token*), NULL, NULL);
	while (cstream_peek(tkstream->cstream) > -1)
	{
		ast->tokens = (t_token**)v_tokens.begin;
		token = (t_token**)ft_vector_push_back(&v_tokens, NULL);
		if (!token)
			return (error_string(ERR_MEMORY));
		else if (!(*token = ast_parse_expr(tkstream)))
		{
			if (cstream_peek(tkstream->cstream) < -1)
			{
				ft_dprintf(STDERR_FILENO, "error: \"%s\": file read error\n",
						tkstream->cstream->file_path);
				return (0);
			}
			return (1);
		}
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
			return (NULL);
		}
	}
	else
		error_string(ERR_MEMORY);
	tkstream_close(&tkstream);
	return (ast);
}

void				ast_destroy(t_ast **ast)
{
	int			i;

	if (!ast)
		return ;
	if (*ast)
	{
		i = -1;
		while (++i + 1 && (*ast)->tokens[i])
			token_destroy(&(*ast)->tokens[i]);
		if ((*ast)->tokens)
			ft_memdel((void**)(*ast)->tokens);
		ft_memdel((void**)ast);
	}
}
