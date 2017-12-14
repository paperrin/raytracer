/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:14:42 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/14 19:58:46 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			app_create(t_app *app)
{
	if (!window_create(&app->win, APP_WIDTH, APP_HEIGHT, APP_TITLE))
		return (0);
	window_callback_key(&app->win, &callback_key);
	window_loop(&app->win, app);
	return (1);
}

void		app_destroy(t_app *app, int exit_status)
{
	window_destroy(&app->win);
	exit(exit_status);
}

int			main(int ac, char **av)
{
	t_app				app;
	t_opencl			ocl;
	t_kernel			kernel;
	const float					input[5] = {1, 2, 3, 4, 5};
	float						output[5];
	cl_mem						d_input;
	cl_mem						d_output;
	size_t len;
	const size_t				work_size = 5;

	(void)ac;
	(void)av;

	if (!(opencl_init(&ocl)))
		return (EXIT_FAILURE);

	d_input = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(*input) * 5, (void*)input, 0);
	d_output = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, sizeof(*input) * 5, 0, 0);

	/*-----------------------------------------------KERNEL ROUTINE___________*/
	opencl_kernel_init(&ocl, &kernel, "./src_cl/add42.cl", NULL);
	/*----------------------------------------END KERNEL ROUTINE-------------------*/
	clSetKernelArg(kernel.kernel, 0, sizeof(cl_mem), (void *) &d_input);
	clSetKernelArg(kernel.kernel, 1, sizeof(cl_mem), (void *) &d_output);
	clEnqueueNDRangeKernel(ocl.cmd_queue, kernel.kernel, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(ocl.cmd_queue, d_output, CL_TRUE, 0, work_size * sizeof(float), output, 0, NULL, NULL);
	len = 0;
	while (len < work_size)
	{
		printf("%f\n", output[len]);
		len++;
	}

	opencl_release_all(&ocl);

	if (!app_create(&app))
		return (EXIT_FAILURE);
	app_destroy(&app, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
