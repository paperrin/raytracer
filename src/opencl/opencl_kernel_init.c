/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernel_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:59:51 by alngo             #+#    #+#             */
/*   Updated: 2017/12/16 22:00:34 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

void		opencl_kernel_init(t_ocl_kernel *kernel, t_opencl *ocl)
{
	kernel->ocl = ocl;
}