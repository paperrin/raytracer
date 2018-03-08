/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernel_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 16:48:00 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/16 19:46:45 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"
#include "rt.h"

void					opencl_kernel_arg_select_id(t_ocl_kernel *kernel
		, size_t id)
{
	kernel->selected_arg_id = id;
}

int						opencl_kernel_arg_selected_create(t_ocl_kernel *kernel
		, cl_mem_flags flags, size_t size, void *host_ptr)
{
	size_t		id;
	cl_int		err;

	id = kernel->selected_arg_id;
	kernel->args[id] = clCreateBuffer(kernel->ocl->context, flags, size
			, host_ptr, &err);
	if (err != CL_SUCCESS)
		return (error_cl_code(err));
	if (CL_SUCCESS != (err = clSetKernelArg(kernel->kernel, id,
					sizeof(cl_mem), (void*)&kernel->args[id])))
		return (error_cl_code(err));
	return (1);
}

int						opencl_kernel_arg_selected_use_kernel_arg_id(
		t_ocl_kernel *kernel, t_ocl_kernel *kernel_src, size_t id)
{
	cl_int		err;

	if (CL_SUCCESS != (err = clSetKernelArg(kernel->kernel,
					kernel->selected_arg_id, sizeof(cl_mem)
			, (void*)&kernel_src->args[id])))
		return (error_cl_code(err));
	return (1);
}

void					opencl_kernel_arg_selected_destroy(
		t_ocl_kernel *kernel)
{
	clReleaseMemObject(kernel->args[kernel->selected_arg_id]);
}
