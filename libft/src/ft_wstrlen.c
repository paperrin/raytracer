/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:25:54 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/12 19:14:14 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

size_t		ft_wstrlen(const wchar_t *ws)
{
	int		i;

	i = 0;
	while (ws[i])
		i++;
	return (i);
}

size_t		ft_wstrlen_char(const wchar_t *ws)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (ws[i])
	{
		len += ft_wchar_len(ws[i]);
		i++;
	}
	return (len);
}

size_t		ft_wstrnlen(const wchar_t *ws, size_t n_bytes)
{
	int		i;
	size_t	char_len;
	size_t	len;

	i = -1;
	len = 0;
	while (ws[++i])
	{
		char_len = ft_wchar_len(ws[i]);
		if (len + char_len <= n_bytes)
			len += char_len;
		else
			return (i);
	}
	return (i);
}

size_t		ft_wstrnlen_char(const wchar_t *ws, size_t n_bytes)
{
	int		i;
	size_t	char_len;
	size_t	len;

	i = -1;
	len = 0;
	while (ws[++i])
	{
		char_len = ft_wchar_len(ws[i]);
		if (len + char_len <= n_bytes)
			len += char_len;
		else
			return (len);
	}
	return (len);
}
