/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_punc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:47:41 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 17:04:36 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/token.h"

int				token_punc_print(t_token const *const token,
		unsigned int indent_depth)
{
	token_indent(indent_depth);
	ft_printf("{ type: \"PUNC\", value: \"%c\" }", token->as.punc.value);
	return (1);
}

void			token_punc_destroy(t_token *token)
{
	(void)token;
}
