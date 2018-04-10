/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_call.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:16:41 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 17:07:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/token.h"

static int		token_print_args(t_token const *const token,
		unsigned int indent_depth)
{
	int			i;

	token_indent(indent_depth + 1);
	ft_putstr("args: [ ");
	if (token->as.call.args_len)
	{
		ft_putendl("");
		i = -1;
		while (++i < token->as.call.args_len)
		{
			if (!token_print(token->as.call.args[i], indent_depth + 2))
				return (0);
			if (i + 1 < token->as.call.args_len)
				ft_putendl(",");
		}
		ft_putendl("");
		token_indent(indent_depth + 1);
	}
	ft_putendl("]");
	return (1);
}

int				token_call_print(t_token const *const token,
		unsigned int indent_depth)
{
	token_indent(indent_depth);
	ft_putendl("{");
	token_indent(indent_depth + 1);
	ft_putendl("type: \"CALL\",");
	token_indent(indent_depth + 1);
	ft_printf("func: \"%s\",\n", token->as.call.func);
	token_print_args(token, indent_depth);
	token_indent(indent_depth);
	ft_putstr("}");
	return (1);
}

void			token_call_destroy(t_token *token)
{
	int			i;

	ft_memdel((void**)&token->as.call.func);
	i = -1;
	while (++i < token->as.call.args_len)
		token_destroy((t_token**)&token->as.call.args[i]);
	ft_memdel((void**)&token->as.call.args);
	token->as.call.args_len = 0;
}
