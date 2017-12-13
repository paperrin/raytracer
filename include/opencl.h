/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:33:54 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/13 18:15:06 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_H
# define OPENCL_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# include "libft.h"
# include "ft_printf.h"

typedef struct			s_device_info
{
	cl_char				*vendor_name;
	cl_char				*device_name;
}						t_device_info;

typedef struct			s_opencl
{
	cl_int				err;
	cl_device_id		cpu;
	cl_device_id		device;
	t_device_info		device_info;
	cl_context			context;
	cl_command_queue	cmd_queue;
}						t_opencl;

typedef struct			s_kernel
{
	cl_program			program;
	cl_kernel			kernel;
}						t_kernel;

int						opencl_init(t_opencl *ocl);
cl_char					*opencl_get_device_info(cl_device_id device, cl_device_info param_name);
void					opencl_print_device_info(t_device_info const *info);
#endif
