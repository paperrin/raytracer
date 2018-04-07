/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_op_eval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:53:59 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/07 01:56:47 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

int					token_op_eval(t_token const *const tk_expr,
		t_token *const tk_result, t_app *const app)
{
	(void)app;
	*tk_result = *tk_expr;
	return (1);
}
