/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernel_create_n_args.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:51:20 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/05 20:47:10 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"
#include "rt.h"

static int		allocate_n_args(t_ocl_kernel *kernel, unsigned char nb_arg)
{
	kernel->args_size = 0;
	if (!(kernel->args = (cl_mem *)ft_memalloc(sizeof(cl_mem) * nb_arg)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	kernel->args_size = nb_arg;
	return (1);
}

int				opencl_kernel_create_n_args(t_ocl_kernel *kernel
		, t_opencl *ocl, unsigned char nb_args)
{
	kernel->ocl = ocl;
	if (!allocate_n_args(kernel, nb_args))
	{
		opencl_kernel_destroy(kernel);
		return (0);
	}
	return (1);
}
