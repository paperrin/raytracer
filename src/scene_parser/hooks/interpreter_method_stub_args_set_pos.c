/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_method_stub_args_set_pos.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 15:02:12 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 21:34:07 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

int				interpreter_method_stub_args_set_pos(
		t_hook_args const *const args, t_real3 *const pos)
{
	if (!hook_valid_args(args, 3
				, token_type_num, token_type_num, token_type_num))
		return (0);
	*pos = vec3r(
			args->tokens[0].as.num.value,
			args->tokens[1].as.num.value,
			args->tokens[2].as.num.value);
	return (1);
}
