/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_devices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:44:45 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/28 19:25:58 by paperrin         ###   ########.fr       */
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

static int	get_devices(cl_platform_id platform)
{
	cl_uint			device_nb;
	cl_device_id	*devices;
	cl_char			*device_name;
	cl_int			i;

	i = -1;
	if (!(device_nb = opencl_get_device_number(platform)))
		return (0);
	if (!(devices = opencl_get_device_ids(platform)))
		return (0);
	while (++i < (int)device_nb)
	{
		device_name = opencl_get_device_info(devices[i]
				, CL_DEVICE_NAME);
		printf("\tDevice %u: %s\n", i, device_name);
		ft_memdel((void**)&device_name);
	}
	free(devices);
	return (1);
}

static int	get_platforms(cl_uint pf_nb)
{
	cl_int				i;
	cl_platform_id		*platforms;
	cl_char				*platform_n;

	i = -1;
	if (!(platforms = opencl_get_platform_ids()))
		return (0);
	while (++i < (int)pf_nb)
	{
		if (!(platform_n = opencl_get_platform_info(
				platforms[i], CL_PLATFORM_NAME)))
			break ;
		ft_printf("\nPlatform %u: %s\n", i, platform_n);
		ft_memdel((void**)&platform_n);
		if (!get_devices(platforms[i]))
			break ;
	}
	ft_memdel((void**)&platforms);
	if (i < (int)pf_nb)
		return (0);
	ft_printf("\n" APP_USAGE);
	return (1);
}

int			arg_devices(t_opencl *ocl, const char *args)
{
	cl_uint				platform_nb;
	cl_char				*name_str;

	if ((platform_nb = opencl_get_platform_number())
			&& (!args || !args[0]))
	{
		name_str = NULL;
		if (get_platforms(platform_nb))
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
