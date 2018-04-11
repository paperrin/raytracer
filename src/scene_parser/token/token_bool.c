/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:53:24 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 18:35:24 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/token.h"

void		token_bool_destroy(t_token *token)
{
	(void)token;
}

t_token		token_bool(int value)
{
	t_token		token;

	token.type = token_type_bool;
	token.as.boolean.value = value;
	return (token);
}
