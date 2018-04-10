/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_devices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:44:45 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/08 19:30:28 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_ids(t_opencl *ocl, cl_uint platform_id, cl_uint device_id)
{
	cl_device_id		device;
	cl_platform_id		platform;

	if (!(platform = opencl_get_platform_id(platform_id)))
	{
		error_string("error: invalid platform id");
		return (0);
	}
	if (!(device = opencl_get_device_id(platform, device_id)))
	{
		error_string("error: invalid device id");
		return (0);
	}
	ocl->platform_id = platform_id;
	ocl->device_id = device_id;
	clReleaseDevice(device);
	return (1);
}

/*
** Potential leaks here (device/platform_info)
*/

static int	get_devices(cl_platform_id *platforms, cl_uint pid,
		cl_char *device_name)
{
	cl_uint			device_nb;
	cl_device_id	*devices;
	cl_uint			i;

	i = -1;
	device_nb = opencl_get_device_number(platforms[pid]);
	devices = opencl_get_device_ids(platforms[pid]);
	while (++i < device_nb)
	{
		if (device_name)
			free(device_name);
		device_name = opencl_get_device_info(devices[i]
				, CL_DEVICE_NAME);
		printf("\tDevice %u: %s\n", i, device_name);
		clReleaseDevice(devices[i]);
	}
	free(devices);
	return (1);
}

static int	get_platforms(cl_uint pf_nb, cl_char *platform_n)
{
	cl_uint				i;
	cl_platform_id		*platforms;

	i = -1;
	platforms = opencl_get_platform_ids();
	while (++i < pf_nb)
	{
		if (platform_n)
			free(platform_n);
		platform_n = opencl_get_platform_info(platforms[i], CL_PLATFORM_NAME);
		ft_printf("\nPlatform %u: %s\n", i, platform_n);
		if (!get_devices(platforms, i, platform_n))
			return (0);
	}
	free(platforms);
	ft_printf("\nusage: rt -d <platform_id>:<device_id>\n");
	return (1);
}

int			arg_devices(t_opencl *ocl, const char *args)
{
	cl_uint				platform_nb;
	cl_char				*name_str;

	if ((platform_nb = opencl_get_platform_number()) && (!args || !args[0]))
	{
		name_str = NULL;
		if (get_platforms(platform_nb, name_str))
			return (1);
		return (0);
	}
	else if (ft_isdigit(args[0]) && args[1] == ':' && ft_isdigit(args[2]))
	{
		if (!check_ids(ocl, ft_atoi(&args[0]), ft_atoi(&args[2])))
			return (0);
		return (2);
	}
	error_string("error: invalid flag arguments");
	return (0);
}
