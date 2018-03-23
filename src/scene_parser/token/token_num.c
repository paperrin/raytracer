/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 19:01:08 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/23 19:38:59 by paperrin         ###   ########.fr       */
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
