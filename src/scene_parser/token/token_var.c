/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:57:01 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 17:06:37 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/token.h"

int				token_var_print(t_token const *const token,
		unsigned int indent_depth)
{
	token_indent(indent_depth);
	ft_printf("{ type: \"VAR\", name: \"%s\" }", token->as.var.name);
	return (1);
}

void			token_var_destroy(t_token *token)
{
	ft_memdel((void**)&token->as.var.name);
}
