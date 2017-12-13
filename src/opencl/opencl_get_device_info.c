/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_get_device_info.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:05:43 by alngo             #+#    #+#             */
/*   Updated: 2017/12/13 18:14:24 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

cl_char		*opencl_get_device_info(cl_device_id device, cl_device_info param_name)
{
	cl_char	*str;
	size_t	size;

	if((clGetDeviceInfo(device, param_name, 1024, NULL, &size) != CL_SUCCESS))
		return (NULL);
	str = (cl_char *)ft_strnew(sizeof(char) * size);
	if((clGetDeviceInfo(device, param_name, size + 1, str, &size) != CL_SUCCESS))
		return (NULL);
	return (str);
}
