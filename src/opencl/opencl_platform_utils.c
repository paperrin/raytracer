/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_platform_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:22:43 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/08 18:14:48 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "opencl.h"

cl_uint				opencl_get_platform_number(void)
{
	cl_uint		platform_number;
	int			err;

	if (CL_SUCCESS != (err = clGetPlatformIDs(0, NULL, &platform_number)))
		return (error_cl_code(err));
	return (platform_number);
}

cl_platform_id		*opencl_get_platform_ids(void)
{
	cl_platform_id	*platforms;
	int				err;
	cl_uint			platform_number;

	if (!(platform_number = opencl_get_platform_number()))
		return (NULL);
	if (!(platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id)
					* platform_number)))
		return (perror_string(ERR_MEMORY));
	if (CL_SUCCESS != (err = clGetPlatformIDs(platform_number,
					platforms, NULL)))
	{
		ft_memdel((void**)&platforms);
		return (perror_cl_code(err));
	}
	return (platforms);
}

cl_platform_id		opencl_get_platform_id(cl_uint id)
{
	cl_platform_id	*platforms;
	cl_platform_id	platform;

	if (opencl_get_platform_number() <= id)
		return (NULL);
	platforms = opencl_get_platform_ids();
	platform = platforms[id];
	free(platforms);
	platforms = NULL;
	return (platform);
}
