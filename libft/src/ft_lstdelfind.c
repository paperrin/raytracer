/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelfind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:37:17 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/10 15:49:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdelfind(t_list *list, void (*del_f)(void*, size_t)
		, void *cmp_data, t_list *(*cmp_f)(t_list*, void*))
{
	t_list	*next;

	if (!list || !cmp_f)
		return (list);
	if ((*cmp_f)(list, cmp_data))
	{
		next = list->next;
		ft_lstdelone(&list, del_f);
		return (next);
	}
	list->next = ft_lstdelfind(list->next, del_f, cmp_data, cmp_f);
	return (list);
}
