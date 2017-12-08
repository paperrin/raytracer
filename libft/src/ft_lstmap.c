/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 20:34:29 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/10 18:20:45 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

static void		del_content(void *content, size_t size)
{
	size = 0;
	if (content)
		free(content);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*new_elem;

	new_elem = NULL;
	while (lst)
	{
		if (!new_elem)
		{
			new_elem = (*f)(lst);
			new_list = new_elem;
		}
		else
		{
			new_elem->next = (*f)(lst);
			new_elem = new_elem->next;
		}
		if (!new_elem)
		{
			ft_lstdel(&new_list, &del_content);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new_list);
}
