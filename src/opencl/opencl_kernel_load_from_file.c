/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernel_load_from_file.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 17:17:06 by alngo             #+#    #+#             */
/*   Updated: 2018/04/27 10:30:26 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./internal_opencl.h"
#include "opencl.h"
#include "rt.h"

static int				opencl_kernel_create_program_with_source(
		t_ocl_kernel *kernel, char const *const path)
{
	cl_int				err;
	char				*src;

	if (!(src = ft_file_to_string(path)))
		return (error_string("could not open source file"));
	kernel->program = clCreateProgramWithSource(kernel->ocl->context
					, 1, (char const **)&src, 0, &err);
	free(src);
	if (err != CL_SUCCESS)
		return (error_cl_code(err));
	return (1);
}

static int				opencl_kernel_build_program(
		t_ocl_kernel *kernel, char const *const flags)
{
	cl_int				err;
	char				*flags_options;

	if (!(flags_options = internal_add_compile_options(flags)))
		return (0);
	if ((err = clBuildProgram(kernel->program, 0, NULL
					, flags_options, NULL, NULL)) != CL_SUCCESS)
	{
		internal_print_program_build_info(kernel->ocl, kernel);
		free(flags_options);
		return (error_cl_code(err));
	}
	free(flags_options);
	return (1);
}

static int				opencl_kernel_create(
		t_ocl_kernel *kernel, char const *const path)
{
	cl_int				err;
	char				*file_name;

	if (!(file_name = internal_path_get_file_name(path)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	kernel->kernel = clCreateKernel(kernel->program, file_name, &err);
	free(file_name);
	if (err != CL_SUCCESS)
		return (error_cl_code(err));
	return (1);
}

int						opencl_kernel_load_from_file(t_ocl_kernel *kernel
		, char const *const path, char const *const flags)
{
	if (!(opencl_kernel_create_program_with_source(kernel, path)))
		return (0);
	if (!(opencl_kernel_build_program(kernel, flags)))
		return (0);
	if (!(opencl_kernel_create(kernel, path)))
		return (0);
	return (1);
}
