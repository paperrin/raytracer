/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_method_stub_args_set_rot.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 16:35:45 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/23 19:42:12 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

int				interpreter_method_stub_args_set_rot(
		t_hook_args const *const args,
		t_real3 *const dir1, t_real3 *const dir2, t_real3 *const dir3)
{
	t_matrix		mx;

	if (!hook_valid_args(args, 3
			, token_type_num, token_type_num, token_type_num))
		return (0);
	ft_matrix_to_identity(&mx);
	ft_matrix_rot(&mx
			, args->tokens[0].as.num.value / 180.f * M_PI
			, args->tokens[1].as.num.value / 180.f * M_PI
			, args->tokens[2].as.num.value / 180.f * M_PI);
	if (dir1)
	{
		scene_transform(dir1, &mx);
		*dir1 = vec3r_norm(*dir1);
	}
	if (dir2)
	{
		scene_transform(dir2, &mx);
		*dir2 = vec3r_norm(*dir2);
	}
	if (dir3)
	{
		scene_transform(dir3, &mx);
		*dir3 = vec3r_norm(*dir3);
	}
	return (1);
}
