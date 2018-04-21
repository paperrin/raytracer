/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_config_method_screen_size.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 06:37:57 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 06:54:37 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_config_methods.h"

int			f_internal_config_method_screen_size(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_config		*config;

	*tk_return = *tk_this;
	config = &interpreter->app->config;
	if (!hook_valid_args(&args, 2, token_type_num, token_type_num))
		return (0);
	config->screen_size.s[0] = ft_clamp(args.tokens[0].as.num.value, 72, 4096);
	config->screen_size.s[1] = ft_clamp(args.tokens[1].as.num.value, 48, 2160);
	return (1);
}
