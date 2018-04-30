/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_device_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 17:18:13 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/18 03:25:43 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "opencl.h"

cl_uint			opencl_get_device_number(cl_platform_id platform)
{
	cl_uint		device_number;
	int			err;

	if (CL_SUCCESS != (err = clGetDeviceIDs(platform,
					CL_DEVICE_TYPE_ALL, 0, NULL, &device_number)))
		return (error_cl_code(err));
	return (device_number);
}

cl_device_id	*opencl_get_device_ids(cl_platform_id platform)
{
	cl_device_id	*devices;
	cl_uint			device_number;
	int				err;

	if (!(device_number = opencl_get_device_number(platform)))
		return (NULL);
	if (!(devices = (cl_device_id*)malloc(
					sizeof(cl_device_id) * device_number)))
		return (perror_string(ERR_MEMORY));
	if (CL_SUCCESS != (err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL,
						device_number, devices, NULL)))
	{
		ft_memdel((void**)&devices);
		return (perror_cl_code(err));
	}
	return (devices);
}

cl_device_id	opencl_get_device_id(cl_platform_id platform, cl_uint id)
{
	cl_device_id	device;
	cl_device_id	*devices;
	int				err;

	if (id != 42 && opencl_get_device_number(platform) <= id)
		return (NULL);
	if (id != 42)
	{
		devices = opencl_get_device_ids(platform);
		device = devices[id];
		free(devices);
		devices = NULL;
	}
	else
	{
		if (CL_SUCCESS != (err = clGetDeviceIDs(platform
						, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL)))
			return (perror_cl_code(err));
	}
	return (device);
}
