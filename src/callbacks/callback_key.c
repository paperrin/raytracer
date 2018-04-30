/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:52:27 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 22:43:13 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "rt.h"

char		*get_unique_file_name(const char *path, const char *ext)
{
	char		*name;
	time_t		mytime;
	struct tm	*info;
	int			millisec;

	millisec = 0;
	time(&mytime);
	info = localtime(&mytime);
	name = NULL;
	while (millisec <= 1000)
	{
		if (!millisec)
			ft_asprintf(&name, "%s%d-%d-%d at %d.%d.%d.%s",
			path, info->tm_year + 1900, info->tm_mon + 1, info->tm_mday,
			info->tm_hour, info->tm_min, info->tm_sec, ext);
		else
			ft_asprintf(&name, "%s%d-%d-%d at %d.%d.%d (%d).%s"
			, path, info->tm_year + 1900, info->tm_mon + 1, info->tm_mday,
			info->tm_hour, info->tm_min, info->tm_sec, millisec, ext);
		if (name && !(access(name, F_OK)))
			millisec++;
		else
			break ;
	}
	return (name);
}

int			save_screenshot(t_app *app)
{
	t_ppm_file	file;
	char		*name;

	file.type = '6';
	file.width = app->win.width;
	file.height = app->win.height;
	file.max_val = 255;
	file.color_depth_vector = ft_ppm_from_floats(&file, app->draw_buf.pixels);
	if (!(name = get_unique_file_name(APP_SCREENSHOT_PATH, "ppm")))
		return (0);
	if ((file.fd = open(name, O_CREAT | O_RDWR, S_IRWXU)) == -1
		|| !(ft_ppm_file_write(&file)))
	{
		ft_strdel(&name);
		return (0);
	}
	ft_printf("Saved screenshot at: \"%s\"\n", name);
	ft_strdel(&name);
	ft_memdel((void **)&file.color_depth_vector);
	return (1);
}

void		callback_key(void *user_ptr, int key, int action)
{
	t_app	*app;

	app = (t_app*)user_ptr;
	(void)action;
	if (key == GLFW_KEY_ESCAPE)
		app_destroy(app, EXIT_SUCCESS);
	else if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		app->mouse_captured = !app->mouse_captured;
		if (app->mouse_captured)
			glfwSetInputMode(app->win.glfw_win, GLFW_CURSOR,
					GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(app->win.glfw_win, GLFW_CURSOR,
					GLFW_CURSOR_NORMAL);
	}
	else if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
	{
		save_screenshot(app);
	}
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
		app->config.shading_model = !app->config.shading_model;
	else if (key == GLFW_KEY_T && action == GLFW_PRESS)
		app->config.fxaa = !app->config.fxaa;
}
