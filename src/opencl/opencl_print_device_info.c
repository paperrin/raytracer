/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_print_device_info.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:05:56 by alngo             #+#    #+#             */
/*   Updated: 2017/12/13 18:11:41 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

void		opencl_print_device_info(t_device_info const *info)
{
	ft_printf("Using:\n\tvendor: %s\n\tmodel: %s\n", info->vendor_name, info->device_name);
}
