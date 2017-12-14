/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:04:50 by alngo             #+#    #+#             */
/*   Updated: 2017/12/14 14:09:13 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

static int			set_device(t_opencl *ocl)
{
	cl_int			err;
	cl_device_id	cpu;

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &cpu, NULL);
	if (clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &(ocl->device), NULL)
			!= CL_SUCCESS)
	{
		if (err != CL_SUCCESS)
			return (0);
		ocl->device = cpu;
		clReleaseDevice(cpu);
	}
	return (1);
}

static int			set_and_print_device_info(t_opencl *ocl)
{
	ocl->device_info.vendor_name = opencl_get_device_info(ocl->device
			, CL_DEVICE_VENDOR);
	ocl->device_info.device_name = opencl_get_device_info(ocl->device
			, CL_DEVICE_NAME);
	if (!ocl->device_info.vendor_name || !ocl->device_info.device_name)
	{
		if (ocl->device_info.vendor_name)
			free(ocl->device_info.device_name);
		else
			free(ocl->device_info.vendor_name);
		return (0);
	}
	opencl_print_device_info(&ocl->device_info);
	return (1);
}

int					opencl_init(t_opencl *ocl)
{
	cl_int			err;

	if (!set_device(ocl))
		return (0);
	if (!set_and_print_device_info(ocl))
	{
		clReleaseDevice(ocl->device);
		return (0);
	}
	ocl->context = clCreateContext(0, 1, &(ocl->device), NULL, NULL
			, &err);
	if (err)
		return (0);
	ocl->cmd_queue = clCreateCommandQueue(ocl->context, ocl->device, 0
			, &err);
	if (err)
	{
		clReleaseContext(ocl->context);
		return (0);
	}
	return (1);
}
