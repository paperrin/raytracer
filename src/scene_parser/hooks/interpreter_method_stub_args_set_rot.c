/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_method_stub_args_set_rot.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 16:35:45 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 18:07:40 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

static void		transform_dir_if_is_not_null(
		t_real3 *dir, t_matrix const *const mx)
{
	if (dir)
	{
		scene_transform(dir, mx);
		*dir = vec3r_norm(*dir);
	}
}

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
	transform_dir_if_is_not_null(dir1, &mx);
	transform_dir_if_is_not_null(dir2, &mx);
	transform_dir_if_is_not_null(dir3, &mx);
	return (1);
}
