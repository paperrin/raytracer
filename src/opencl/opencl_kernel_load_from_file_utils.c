/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernel_load_from_file_utils.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 17:12:22 by alngo             #+#    #+#             */
/*   Updated: 2017/12/17 17:49:05 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_opencl.h"
#include "opencl.h"
#include "rt.h"

char		*internal_path_get_file_name(char const *const path)
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

int			internal_print_program_build_info(
		t_opencl *ocl, t_ocl_kernel *kernel)
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

char		*internal_add_compile_options(char const *const flags)
{
	char	*new_flags;

	if (!(new_flags = ft_strjoin(flags, " -D IS_KERNEL")))
		return (catch_perror(CL_OUT_OF_HOST_MEMORY));
	return (new_flags);
}
