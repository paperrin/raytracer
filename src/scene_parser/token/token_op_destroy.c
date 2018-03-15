/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_op_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:43:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/15 17:49:10 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

void		token_op_destroy(t_token *token)
{
	if (token->as.op.left)
		token_destroy(&token->as.op.left);
	if (token->as.op.right)
		token_destroy(&token->as.op.right);
}
