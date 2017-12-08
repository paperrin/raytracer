/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:34:22 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/13 16:25:43 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **list, t_list *elem)
{
	t_list	*cur;

	if (!*list)
	{
		*list = elem;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = elem;
}
