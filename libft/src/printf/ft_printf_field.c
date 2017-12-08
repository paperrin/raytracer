/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_field.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 15:14:18 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:15:28 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf_field		ft_printf_field(int min, int precision)
{
	t_printf_field		field;

	field.min = min;
	field.precision = precision;
	return (field);
}
