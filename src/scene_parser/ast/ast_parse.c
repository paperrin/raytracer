/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:21:37 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/12 15:39:32 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

static int			parse_program(t_ast *const ast,
		t_token_stream *const tkstream)
{
	t_token		*token;

	if (!(token = tkstream_peek(tkstream)))
		return (0);

	(void)ast;
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
			ast_destroy(&ast);
	}
	else
		error_string(ERR_MEMORY);
	tkstream_close(&tkstream);
	return (ast);
}

void				ast_destroy(t_ast **ast)
{
	int			i;

	i = -1;
	while (++i + 1 && (*ast)->tokens[i])
		token_destroy(&(*ast)->tokens[i]);
	ft_memdel((void**)&(*ast)->tokens);
	ft_memdel((void**)ast);
}
