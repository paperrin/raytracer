/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:33:54 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/29 16:48:27 by paperrin         ###   ########.fr       */
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
# include "ft_file.h"
# include "ft_vector.h"

# define CL_UNKNOWN_ERROR_CODE -64

typedef struct			s_ocl_device_info
{
	cl_char				*vendor_name;
	cl_char				*device_name;
}						t_ocl_device_info;

typedef struct			s_opencl
{
	cl_int				err;
	cl_device_id		device;
	t_ocl_device_info	device_info;
	cl_context			context;
	cl_command_queue	cmd_queue;
}						t_opencl;

typedef struct			s_ocl_kernel
{
	t_opencl			*ocl;
	size_t				work_size;
	size_t				selected_arg_id;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				*args;
	unsigned char		args_size;
}						t_ocl_kernel;

int						opencl_create(t_opencl *ocl, int use_gpu);
void					opencl_destroy(t_opencl *ocl);
cl_char					*opencl_get_device_info(cl_device_id device
		, cl_device_info param_name);
void					opencl_print_device_info(
		t_ocl_device_info const *info);

int						opencl_kernel_create_n_args(t_ocl_kernel *kernel
		, t_opencl *ocl, unsigned char nb_args);
int						opencl_kernel_load_from_file(t_ocl_kernel *kernel
		, char const *const path, char const *const flags);
int						opencl_kernel_destroy(t_ocl_kernel *kernel);

void					opencl_kernel_arg_select_id(t_ocl_kernel *kernel
		, size_t id);
int						opencl_kernel_arg_selected_create(t_ocl_kernel *kernel
		, cl_mem_flags flags, size_t size, void *host_ptr);
int						opencl_kernel_arg_set(t_ocl_kernel *kernel, size_t id,
		size_t arg_size, void const *arg_value);
int						opencl_kernel_arg_selected_use_kernel_arg_id(
		t_ocl_kernel *kernel, t_ocl_kernel *kernel_src, size_t id);
void					opencl_kernel_arg_selected_destroy(
		t_ocl_kernel *kernel);

#endif
