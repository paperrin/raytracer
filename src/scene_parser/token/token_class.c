/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:50:49 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 15:55:24 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/token.h"

t_token		token_class(t_e_class_type class_type, void *const ptr)
{
	t_token		tk;

	tk.type = token_type_class;
	tk.as.class.class_type = class_type;
	tk.as.class.ptr = ptr;
	return (tk);
}
