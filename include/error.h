/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 20:37:51 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/27 13:35:42 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define ERR_MEMORY "not enough memory"

int		error_cl_code(cl_int err_code);
void	*perror_cl_code(cl_int err_code);
int		error_string(char const *const error_str);
void	*perror_string(char const *const str_error);
int		error_string_2(char const *const str_error,
		char const *const str_error2);

#endif
