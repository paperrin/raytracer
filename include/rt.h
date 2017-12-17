/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:36:38 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/17 22:56:57 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "opencl.h"
# include "window.h"
# include "ft_vector.h"
# include "shared.h"
# include "vec.h"
# include "image.h"

# define APP_WIDTH 1600
# define APP_HEIGHT 900
# define APP_TITLE "RT"

typedef struct		s_scene
{
	t_vector		v_obj;
}					t_scene;

typedef struct		s_app
{
	t_window	win;
	t_scene		scene;
	t_camera	cam;
	t_image		draw_buf;
}					t_app;

int					app_create(t_app *app);
void				app_destroy(t_app *app, int exit_status);

void				callback_key(void *user_ptr, int key, int action);

cl_int				catch_error(cl_int err_code);
void				*catch_perror(cl_int err_code);

t_obj				obj_sphere(t_real3 pos, t_real radius, t_mat_id material);

int					render(t_app *app);

#endif
