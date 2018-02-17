/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:09:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/02/22 21:30:40 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "global.h"

int			error_cl_code(cl_int err_code)
{
	size_t		i;

	i = 0;
	if (err_code >= -63 && err_code <= 0)
		ft_dprintf(STDERR_FILENO, "error: %s\n", g_error_strings[-err_code]);
	else
		ft_dprintf(STDERR_FILENO, "error: %s\n", g_error_strings[64]);
	return (0);
}

void		*perror_cl_code(cl_int err_code)
{
	error_cl_code(err_code);
	return (NULL);
}

int			error_string(char const *const str_error)
{
	ft_dprintf(STDERR_FILENO, "error: %s\n", str_error);
	return (0);
}

void		*perror_string(char const *const str_error)
{
	error_string(str_error);
	return (NULL);
}
