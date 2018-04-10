/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:57:01 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/08 18:39:55 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

void	opencl_destroy(t_opencl *ocl)
{
	if (ocl->device_info.device_name)
		free(ocl->device_info.device_name);
	if (ocl->device_info.vendor_name)
		free(ocl->device_info.vendor_name);
	if (ocl->device)
		clReleaseDevice(ocl->device);
	if (ocl->context)
		clReleaseContext(ocl->context);
	if (ocl->cmd_queue)
		clReleaseCommandQueue(ocl->cmd_queue);
}
