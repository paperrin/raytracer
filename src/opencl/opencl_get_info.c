/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_get_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 20:49:41 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/18 03:13:47 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"
#include "error.h"

cl_char			*opencl_get_device_info(cl_device_id device
		, cl_device_info param_name)
{
	cl_char		*str;
	size_t		size;
	int			err;

	if (CL_SUCCESS != (err = clGetDeviceInfo(device, param_name, 0, NULL
			, &size)))
		return ((cl_char*)perror_cl_code(err));
	if (!(str = (cl_char *)ft_strnew(sizeof(char) * size)))
		return ((cl_char*)perror_cl_code(CL_OUT_OF_HOST_MEMORY));
	if (CL_SUCCESS != (err = clGetDeviceInfo(device, param_name, size, str
			, &size)))
	{
		free(str);
		return ((cl_char*)perror_cl_code(err));
	}
	return (str);
}

cl_char			*opencl_get_platform_info(cl_platform_id platform,
		cl_platform_info param_name)
{
	cl_char		*str;
	size_t		size;
	int			err;

	if (CL_SUCCESS != (err = clGetPlatformInfo(platform, param_name, 0, NULL
			, &size)))
		return ((cl_char*)perror_cl_code(err));
	if (!(str = (cl_char*)malloc(sizeof(cl_char) * size)))
		return ((cl_char*)perror_cl_code(CL_OUT_OF_HOST_MEMORY));
	if (CL_SUCCESS != (err = clGetPlatformInfo(platform, param_name, size, str
			, NULL)))
	{
		ft_memdel((void**)&str);
		return ((cl_char*)perror_cl_code(err));
	}
	return (str);
}
