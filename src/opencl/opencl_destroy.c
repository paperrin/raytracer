/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:57:01 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/21 15:57:03 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

void	opencl_destroy(t_opencl *ocl)
{
	if (ocl->device_info.device_name)
		free(ocl->device_info.device_name);
	if (ocl->device_info.vendor_name)
		free(ocl->device_info.vendor_name);
	clReleaseDevice(ocl->device);
	clReleaseContext(ocl->context);
	clReleaseCommandQueue(ocl->cmd_queue);
}
