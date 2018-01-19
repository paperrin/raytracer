/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_mouse_motion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:24:37 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/19 19:22:26 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		callback_mouse_motion(void *user_ptr, double x, double y)
{
	t_app			*app;

	app = (t_app*)user_ptr;
	(void)x;
	(void)y;
}
