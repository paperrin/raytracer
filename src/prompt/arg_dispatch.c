/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:35:22 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/08 19:46:46 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		arg_dispatch(t_opencl *ocl, const char *argv[])
{
	int		ret;

	ocl->platform_id = 0;
	ocl->device_id = 42;
	if (!argv[1] || !argv[1][0])
		return (1);
	if (argv[1][0] != '-' && !error_string("error: invalid argument(s)\n"))
		return (0);
	else if (argv[1][1] == 'd')
	{
		if (2 == (ret = arg_devices(ocl, argv[2])))
			return (1);
		if (ret == 1 || !ret)
			return (0);
	}
	return (0);
}
