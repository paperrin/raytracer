/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:54:50 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 17:06:54 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/token.h"

int				token_str_print(t_token const *const token,
		unsigned int indent_depth)
{
	token_indent(indent_depth);
	ft_printf("{ type: \"STR\", value: \"%s\" }", token->as.str.value);
	return (1);
}

void			token_str_destroy(t_token *token)
{
	ft_memdel((void**)&token->as.str.value);
}
