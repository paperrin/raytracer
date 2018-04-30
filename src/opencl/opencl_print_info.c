/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_print_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 20:49:11 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/18 03:16:14 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

void		opencl_print_device_info(t_ocl_device_info const *info)
{
	ft_printf("Using:\n\tvendor: %s\n\tmodel: %s\n"
			, info->vendor_name, info->device_name);
}

void		opencl_print_platform_info(t_ocl_platform_info const *info)
{
	ft_printf("Opencl version: %s\nCurrent platform: %s\n"
				"Supported platforms: %s\n"
			, info->platform_version, info->platform_name,
			info->supported_extensions);
}
