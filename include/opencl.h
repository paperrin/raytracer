/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:33:54 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/08 18:22:56 by tlernoul         ###   ########.fr       */
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

typedef struct			s_ocl_platform_info
{
	cl_char				*platform_version;
	cl_char				*platform_name;
	cl_char				*supported_extensions;
}						t_ocl_platform_info;

typedef struct			s_opencl
{
	cl_int				err;
	cl_uint				device_id;
	cl_device_id		device;
	cl_uint				platform_id;
	cl_platform_id		platform;
	t_ocl_device_info	device_info;
	t_ocl_platform_info	platform_info;
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

int						opencl_create(t_opencl *ocl);
void					opencl_destroy(t_opencl *ocl);
cl_char					*opencl_get_device_info(cl_device_id device
		, cl_device_info param_name);
cl_char					*opencl_get_platform_info(cl_platform_id platform
		, cl_platform_info param_name);
void					opencl_print_platform_info(
		t_ocl_platform_info const *info);
void					opencl_print_device_info(
		t_ocl_device_info const *info);

cl_uint					opencl_get_platform_number(void);
cl_platform_id			*opencl_get_platform_ids(void);
cl_platform_id			opencl_get_platform_id(cl_uint id);
cl_uint					opencl_get_device_number(cl_platform_id platform);
cl_device_id			*opencl_get_device_ids(cl_platform_id platform);
cl_device_id			opencl_get_device_id(cl_platform_id platform,
														cl_uint id);

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
