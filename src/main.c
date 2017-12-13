/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:14:42 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/12 21:02:08 by alngo            ###   ########.fr       */
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
	cl_int                      err;
	cl_context                  context;
	cl_device_id                cpu;
	cl_device_id                device;
	cl_command_queue            cmd_queue;
	cl_char                     vendor_name[1024];
	cl_char                     device_name[1024];
	const float					input[5] = {1, 2, 3, 4, 5};
	float						output[5];
	cl_mem						d_input;
	cl_mem						d_output;
	cl_program					program;
	cl_kernel					kernel;
	size_t len;
	const size_t				work_size = 5;
	char *buffer;
	const char *source = "__kernel void add42(__global float *in, __global float *out)"
	"{"
   	"	unsigned int i = get_global_id(0);"
	"	out[i] = in[i] + 42;"	
	"}";

	(void)ac;
	(void)av;
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &cpu, NULL);
	if (clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &device, NULL) != CL_SUCCESS)
	{
		if (err != CL_SUCCESS)
			return (EXIT_FAILURE);
		device = cpu;
	}
	if ((clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(vendor_name),
					vendor_name, NULL)
				| clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_name),
					device_name, NULL)) == CL_SUCCESS)
		ft_printf("Using:\n\tvendor: %s\n\tmodel: %s\n", vendor_name, device_name);
	context = clCreateContext(0, 1, &device, NULL, NULL, &err);
	cmd_queue = clCreateCommandQueue(context, device, 0, NULL);
	d_input = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(*input) * 5, (void*)input, 0);
	d_output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(*input) * 5, 0, 0);
	program = clCreateProgramWithSource(context, 1, &source, 0, 0);
	clBuildProgram(program, 0, NULL, NULL, NULL, NULL);



	if ((clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &len) != CL_SUCCESS))
		return (EXIT_FAILURE);
	buffer = ft_memalloc(sizeof(char) * len);
	if ((clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, len, buffer, NULL) == CL_SUCCESS))
	{
		if (len > 1)
		{
			printf("%s\n", buffer);
			return (EXIT_FAILURE);
		}
	}
	else
		return (EXIT_FAILURE);

	kernel = clCreateKernel(program, "add42", NULL);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *) &d_input);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *) &d_output);
	clEnqueueNDRangeKernel(cmd_queue, kernel, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(cmd_queue, d_output, CL_TRUE, 0, work_size * sizeof(float), output, 0, NULL, NULL);
	len = 0;
	while (len < work_size)
	{
		printf("%f\n", output[len]);
		len++;
	}	

	if (!app_create(&app))
		return (EXIT_FAILURE);
	app_destroy(&app, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
