/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_valid_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:29:37 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 19:20:10 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

int			hook_error(char const *const hook_name, char const *const error)
{
	ft_dprintf(STDERR_FILENO, "error: %s(): %s\n", hook_name, error);
	return (0);
}

int			hook_valid_args(t_hook_args const *const passed_args,
		size_t const n_expected_args, ...)
{
	int				i;
	t_e_token_type	arg_type;

	va_list(ap);
	if (n_expected_args < passed_args->size)
	{
		va_end(ap);
		return (hook_error(passed_args->hook_name, "too many arguments"));
	}
	va_start(ap, n_expected_args);
	i = -1;
	while (++i < (int)n_expected_args)
	{
		arg_type = (i < (int)passed_args->size)
			? passed_args->tokens[i].type : token_type_none;
		if (!(arg_type & va_arg(ap, t_e_token_type)))
		{
			va_end(ap);
			return (hook_error(passed_args->hook_name, "invalid arguments"));
		}
	}
	va_end(ap);
	return (1);
}
