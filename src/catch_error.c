/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 20:17:52 by alngo             #+#    #+#             */
/*   Updated: 2017/12/14 22:55:39 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "global.h"

cl_int		catch_error(cl_int err_code)
{
	size_t		i;

	i = 0;
	if (err_code >= -63 && err_code <= 0)
		ft_dprintf(STDERR_FILENO, "Error: %s\n", g_error_strings[-err_code]);
	else
		ft_dprintf(STDERR_FILENO, "Error: %s\n", g_error_strings[64]);
	return (0);
}

void		*catch_perror(cl_int err_code)
{
	catch_error(err_code);
	return (NULL);
}
