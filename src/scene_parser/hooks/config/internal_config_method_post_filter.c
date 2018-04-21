/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_config_method_post_filter.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 06:10:43 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 06:28:52 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_config_methods.h"

int			f_internal_config_method_post_filter(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_config		*config;

	*tk_return = *tk_this;
	config = &interpreter->app->config;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	config->post_filters = ft_maxf(args.tokens[0].as.num.value, 0);
	return (1);
}
