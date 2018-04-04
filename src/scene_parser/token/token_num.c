/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 19:01:08 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/04 23:14:04 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

t_token		*token_num(float value)
{
	t_token		*token;

	if (!(token = (t_token*)malloc(sizeof(*token))))
		return (NULL);
	token->type = token_type_num;
	token->as.num.value = value;
	return (token);
}

int			token_num_print(t_token const *const token,
		unsigned int indent_depth)
{
	char		*value;

	if (!(value = ft_ftoa(token->as.num.value, 5, ".")))
		return (error_string(ERR_MEMORY));
	token_indent(indent_depth);
	ft_printf("{ type: \"NUM\", value: \"%s\" }", value);
	ft_strdel(&value);
	return (1);
}

void		token_num_destroy(t_token *token)
{
	(void)token;
}
