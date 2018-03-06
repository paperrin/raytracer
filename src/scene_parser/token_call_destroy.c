/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_call_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:44:16 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/05 17:51:39 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

void		token_call_destroy(t_token *token)
{
	int			i;

	ft_memdel((void**)&token->as.call.func);
	i = -1;
	while (++i < token->as.call.args_len)
		token_destroy((t_token**)&token->as.call.args[i]);
	ft_memdel((void**)&token->as.call.args);
	token->as.call.args_len = 0;
}
