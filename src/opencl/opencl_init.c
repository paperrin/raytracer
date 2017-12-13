/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:04:50 by alngo             #+#    #+#             */
/*   Updated: 2017/12/13 18:14:58 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

int			opencl_init(t_opencl *ocl)
{
	cl_int	err;

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &(ocl->cpu), NULL);
	if (clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &(ocl->device), NULL) != CL_SUCCESS)
	{
		if (err != CL_SUCCESS)
			return (0);
		ocl->device = ocl->cpu;
	}
	ocl->device_info.vendor_name = opencl_get_device_info(ocl->device, CL_DEVICE_VENDOR);
	ocl->device_info.device_name = opencl_get_device_info(ocl->device, CL_DEVICE_NAME);
	opencl_print_device_info(&(ocl->device_info));
	ocl->context = clCreateContext(0, 1, &(ocl->device), NULL, NULL, &err);
	ocl->cmd_queue = clCreateCommandQueue(ocl->context, ocl->device, 0, NULL);
	return (1);
}
