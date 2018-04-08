/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_opencl.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 17:42:46 by alngo             #+#    #+#             */
/*   Updated: 2018/04/08 16:40:03 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_OPENCL_H
# define INTERNAL_OPENCL_H

# include "opencl.h"

int						internal_print_program_build_info(t_opencl *ocl
		, t_ocl_kernel *kernel);
char					*internal_add_compile_options(char const *const flags);
char					*internal_path_get_file_name(char const *const path);

#endif
