/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_light_method_intensity.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 03:20:56 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 03:31:07 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_light_methods.h"

int				f_internal_light_method_intensity(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)interpreter;
	*tk_return = *tk_this;
	light = tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	light->intensity = ft_maxf(args.tokens[0].as.num.value, 0);
	return (1);
}
