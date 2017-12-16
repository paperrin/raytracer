/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernel_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:59:51 by alngo             #+#    #+#             */
/*   Updated: 2017/12/16 15:07:19 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

static char		*path_get_file_name(char const *const path)
{
	char	*file_name;
	char	*dot;
	int		i;

	if (!path)
		return (catch_perror(CL_INVALID_KERNEL_NAME));
	if (!(file_name = ft_strrchr(path, '/')))
		file_name = (char*)path;
	else
		file_name += 1;
	if (!(dot = ft_strchr(file_name, '.')))
		return (catch_perror(CL_INVALID_KERNEL_NAME));
	if ((i = dot - file_name) < 1)
		return (catch_perror(CL_INVALID_KERNEL_NAME));
	return (ft_strndup(file_name, i));
}

static int		print_program_build_info(t_opencl *ocl, t_ocl_kernel *kernel)
{
	cl_int	err;
	size_t	len;
	char	*buffer;

	if ((err = clGetProgramBuildInfo(kernel->program, ocl->device
					, CL_PROGRAM_BUILD_LOG, 0, NULL, &len)) != CL_SUCCESS)
		return (catch_error(err));
	if (!(buffer = ft_memalloc(sizeof(char) * len)))
		return (catch_error(CL_OUT_OF_HOST_MEMORY));
	if ((err = clGetProgramBuildInfo(kernel->program, ocl->device
		, CL_PROGRAM_BUILD_LOG, len, buffer, NULL)) == CL_SUCCESS && len > 1)
	{
		ft_printf("%s\n", buffer);
		free(buffer);
		return (0);
	}
	else if (err != CL_SUCCESS)
	{
		free(buffer);
		return (catch_error(err));
	}
	return (1);
}

int				opencl_kernel_init(t_opencl *ocl, t_ocl_kernel *kernel
		, char const *const path, char const *const flags)
{
	cl_int	err;
	char	*file_name;
	char	*src;

	if (!(src = ft_file_to_string(path)))
		return (catch_error(CL_UNKNOWN_ERROR_CODE));
	kernel->program = clCreateProgramWithSource(ocl->context, 1
			, (char const **)&src, 0, &err);
	free(src);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	if ((err = clBuildProgram(kernel->program, 0, NULL, flags
					, NULL, NULL)) != CL_SUCCESS)
		return (catch_error(CL_BUILD_PROGRAM_FAILURE));
	if (!print_program_build_info(ocl, kernel))
		return (0);
	if (!(file_name = path_get_file_name(path)))
		return (catch_error(CL_OUT_OF_HOST_MEMORY));
	kernel->kernel = clCreateKernel(kernel->program, file_name, &err);
	free(file_name);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	return (1);
}
