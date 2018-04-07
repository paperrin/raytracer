/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 00:24:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/07 01:58:07 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

int					ast_eval(t_ast const *const ast, t_app *const app)
{
	int		i;
	int		tokens_size;
	t_token	tk_result;

	tokens_size = ft_vector_size(&ast->v_tokens);
	if (!ast || !tokens_size || !app)
		return (0);
	i = -1;
	while (++i < tokens_size)
	{
		if (!token_eval(*(t_token**)ft_vector_at(&ast->v_tokens, i),
					&tk_result, app))
		{
			break ;
		}
	}
	if (i != tokens_size)
		return (0);
	return (1);
}
