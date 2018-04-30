/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernel_destroy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:33:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 03:14:24 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"
#include "rt.h"

int				opencl_kernel_destroy(t_ocl_kernel *kernel)
{
	cl_int		err;

	if (!kernel->program)
		return (0);
	if ((err = clReleaseProgram(kernel->program)) != CL_SUCCESS)
		return (error_cl_code(err));
	if ((err = clReleaseKernel(kernel->kernel)) != CL_SUCCESS)
		return (error_cl_code(err));
	while (kernel->args_size-- > 0)
		clReleaseMemObject(kernel->args[kernel->args_size]);
	return (1);
}
