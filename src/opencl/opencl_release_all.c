/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_release_all.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:31:55 by alngo             #+#    #+#             */
/*   Updated: 2017/12/14 17:48:39 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

void	opencl_release_all(t_opencl *ocl)
{
	if (ocl->device_info.device_name)
		free(ocl->device_info.device_name);
	if (ocl->device_info.vendor_name)
		free(ocl->device_info.vendor_name);
	clReleaseDevice(ocl->device);
	clReleaseContext(ocl->context);
	clReleaseCommandQueue(ocl->cmd_queue);
}
