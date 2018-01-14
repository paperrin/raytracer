/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_compute_texels.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 20:34:13 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/15 00:06:11 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 kernel void			kernel_compute_texels(
		global read_only t_ray_state *ray_states,
		global read_only t_hit *hits,
		global read_write uint *n_hits,
		constant read_only t_obj *objs,
		global write_only t_real3 *texels
		global write_only t_obj_id *hit_objs)
{

*/

int				kernel_compute_texels_create(t_app *app)
{
	size_t		arg_id;

	app->kernel_compute_texels.work_size = APP_WIDTH * APP_HEIGHT;
	if (!(app->texels = (t_texel*)malloc(sizeof(t_texel) * APP_WIDTH * APP_HEIGHT)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	if (!opencl_kernel_create_n_args(&app->kernel_compute_texels, &app->ocl, 6))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_compute_texels
				, "./src/cl/kernel_compute_texels.cl", "-I ./include/ -I ./src/cl/"))
		return (0);

	arg_id = 0;
	while (arg_id < 2)
	{
		opencl_kernel_arg_select_id(&app->kernel_compute_texels, arg_id);
		opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_compute_texels
				, &app->kernel_ray_trace, arg_id);
		arg_id++;
	}
	opencl_kernel_arg_select_id(&app->kernel_compute_texels, 2);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_compute_texels
				, &app->kernel_ray_gen, 2);
	return (1);
}

int				kernel_compute_texels_launch(t_app *app)
{
	size_t		work_size;
	size_t		i;
	size_t		arg_id;

	ft_bzero(app->draw_buf.pixels, sizeof(t_clrf_rgb) * APP_WIDTH * APP_HEIGHT);
	if (app->n_hits < 1)
		return (1);
	app->kernel_compute_texels.work_size = app->n_hits;
	work_size = app->kernel_compute_texels.work_size;
	arg_id = 3;
	while (arg_id < 5)
	{
		opencl_kernel_arg_select_id(&app->kernel_compute_texels, arg_id);
		opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_compute_texels
				, &app->kernel_ray_trace, arg_id);
		arg_id++;
	}
	opencl_kernel_arg_select_id(&app->kernel_compute_texels, 5);
	opencl_kernel_arg_selected_destroy(&app->kernel_compute_texels);
	if (!opencl_kernel_arg_selected_create(&app->kernel_compute_texels
			, CL_MEM_WRITE_ONLY
			, sizeof(t_texel) * app->n_hits, NULL))
		return (0);
	clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_compute_texels.kernel
			, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(app->ocl.cmd_queue, app->kernel_compute_texels.args[5]
			, CL_TRUE, 0, sizeof(t_texel) * app->n_hits, app->texels, 0, NULL, NULL);
	i = -1;
	while (++i < app->n_hits)
	{
		image_set_pixel(&app->draw_buf, app->texels[i].px_id % APP_WIDTH, app->texels[i].px_id / APP_WIDTH
				, ft_clrf_rgb((float)app->texels[i].r, (float)app->texels[i].g, (float)app->texels[i].b));
	}
	return (1);
}

void		kernel_compute_texels_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_compute_texels);
	free(app->texels);
}
