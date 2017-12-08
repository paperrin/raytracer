/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:46:35 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/09 16:44:41 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del_f)(void*, size_t))
{
	(void)del_f;
	if (del_f)
		(*del_f)((*alst)->content, (*alst)->content_size);
	else
		ft_memdel(&(*alst)->content);
	ft_memdel((void**)alst);
}
