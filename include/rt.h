/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:36:38 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/09 16:54:14 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "window.h"

# define APP_WIDTH 720
# define APP_HEIGHT 480
# define APP_TITLE "RT"

typedef struct		s_app
{
	t_window	win;
}					t_app;

int					app_create(t_app *app);
void				app_destroy(t_app *app, int exit_status);

void				callback_key(void *user_ptr, int key, int action);

#endif
