/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:56:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/08 19:55:17 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"
#include "error.h"

static int			set_platform(t_opencl *ocl)
{
	if (!(ocl->platform = opencl_get_platform_id(ocl->platform_id)))
		return (error_cl_code(CL_INVALID_VALUE));
	return (1);
}

static int			set_device(t_opencl *ocl)
{
	if (!(ocl->device = opencl_get_device_id(ocl->platform, ocl->device_id)))
		return (error_cl_code(CL_DEVICE_NOT_FOUND));
	return (1);
}

static int			set_and_print_platform_info(t_opencl *ocl)
{
	ocl->platform_info.platform_version = opencl_get_platform_info(
			ocl->platform, CL_PLATFORM_VERSION);
	ocl->platform_info.platform_name = opencl_get_platform_info(
			ocl->platform, CL_PLATFORM_NAME);
	ocl->platform_info.supported_extensions = opencl_get_platform_info(
			ocl->platform, CL_PLATFORM_EXTENSIONS);
	if (!ocl->platform_info.platform_name ||
				!ocl->platform_info.platform_version ||
							!ocl->platform_info.supported_extensions)
	{
		if (ocl->platform_info.platform_name)
			free(ocl->platform_info.platform_name);
		else if (ocl->platform_info.platform_version)
			free(ocl->platform_info.platform_version);
		else
			free(ocl->platform_info.supported_extensions);
		return (0);
	}
	opencl_print_platform_info(&ocl->platform_info);
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

int					opencl_create(t_opencl *ocl)
{
	cl_int			err;

	if (!set_platform(ocl) || !set_and_print_platform_info(ocl))
		return (0);
	if (!set_device(ocl))
		return (0);
	if (!set_and_print_device_info(ocl))
		return (0);
	ocl->context = clCreateContext(0, 1, &ocl->device, NULL, NULL
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
