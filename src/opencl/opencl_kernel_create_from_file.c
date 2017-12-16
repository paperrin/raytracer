/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernel_create_from_file.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 22:15:27 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/16 22:17:05 by paperrin         ###   ########.fr       */
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

static char		*add_compile_options(char const *const flags)
{
	char		*new_flags;

	if (!(new_flags = ft_strjoin(flags, " -D IS_KERNEL")))
		return (catch_perror(CL_OUT_OF_HOST_MEMORY));
	return (new_flags);
}

static int		allocate_n_args(t_ocl_kernel *kernel, unsigned char nb_arg)
{
	kernel->args_size = 0;
	if (!(kernel->args = (cl_mem *)ft_memalloc(sizeof(cl_mem) * nb_arg)))
		return (catch_error(CL_OUT_OF_HOST_MEMORY));
	kernel->args_size = nb_arg;
	return (1);
}

int				opencl_kernel_create_from_file(t_ocl_kernel *kernel
		, char const *const path, char const *const flags, unsigned char nb_arg)
{
	cl_int	err;
	char	*file_name;
	char	*tmp;

	if (!(tmp = ft_file_to_string(path)))
		return (catch_error(CL_UNKNOWN_ERROR_CODE));
	kernel->program = clCreateProgramWithSource(kernel->ocl->context, 1
			, (char const **)&tmp, 0, &err);
	free(tmp);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	if (!(tmp = add_compile_options(flags)))
		return (0);
	if ((err = clBuildProgram(kernel->program, 0, NULL, tmp, NULL, NULL)) != CL_SUCCESS)
	{
		print_program_build_info(kernel->ocl, kernel);
		free(tmp);
		return (0);
	}
	free(tmp);
	if (!(file_name = path_get_file_name(path)))
		return (catch_error(CL_OUT_OF_HOST_MEMORY));
	kernel->kernel = clCreateKernel(kernel->program, file_name, &err);
	free(file_name);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	if (!allocate_n_args(kernel, nb_arg))
		opencl_kernel_destroy(kernel);
	return (1);
}
