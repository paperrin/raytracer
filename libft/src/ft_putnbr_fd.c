/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:58:47 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 18:30:51 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_math.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	int		div;

	nb = n;
	nb = ft_abs(nb);
	if (n < 0)
		ft_putchar_fd('-', fd);
	div = 1;
	while (nb / div > 9)
		div *= 10;
	while (div > 0)
	{
		ft_putchar_fd('0' + (nb / div), fd);
		nb %= div;
		div /= 10;
	}
}
