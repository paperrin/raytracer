/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:33:54 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/16 22:15:48 by paperrin         ###   ########.fr       */
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
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				*args;
	unsigned char		args_size;
}						t_ocl_kernel;

cl_char					*opencl_get_device_info(cl_device_id device
		, cl_device_info param_name);
int						opencl_init(t_opencl *ocl);
void					opencl_print_device_info(
		t_ocl_device_info const *info);
void					opencl_release_all(t_opencl *ocl);
cl_int					catch_error(cl_int err_code);
void					*catch_perror(cl_int err_code);
int						opencl_kernel_destroy(t_ocl_kernel *kernel);
int				opencl_kernel_create_from_file(t_ocl_kernel *kernel
		, char const *const path, char const *const flags, unsigned char nb_arg);
void		opencl_kernel_init(t_ocl_kernel *kernel, t_opencl *ocl);

#endif
