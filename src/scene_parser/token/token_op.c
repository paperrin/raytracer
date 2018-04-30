/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:35:47 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 17:04:36 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/token.h"

int				token_op_print(t_token const *const token,
		unsigned int indent_depth)
{
	token_indent(indent_depth);
	ft_putendl("{");
	token_indent(indent_depth + 1);
	ft_putendl("type: \"OP\",");
	token_indent(indent_depth + 1);
	ft_printf("value: \"%c\",\n", token->as.op.value);
	token_indent(indent_depth + 1);
	ft_putendl("left:");
	if (!token_print(token->as.op.left, indent_depth + 2))
		return (0);
	ft_putendl(",");
	token_indent(indent_depth + 1);
	ft_putendl("right:");
	if (!token_print(token->as.op.right, indent_depth + 2))
		return (0);
	ft_putendl("");
	token_indent(indent_depth);
	ft_putstr("}");
	return (1);
}

void			token_op_destroy(t_token *token)
{
	if (token->as.op.left)
		token_destroy(&token->as.op.left);
	if (token->as.op.right)
		token_destroy(&token->as.op.right);
}
