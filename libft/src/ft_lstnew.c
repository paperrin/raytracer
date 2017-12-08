/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:05:24 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/13 16:28:52 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*ft_lstnew_should_cpy(void *content, size_t content_size
		, int should_cpy)
{
	t_list	*elem;

	if (!(elem = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
		elem->content = NULL;
	else
	{
		if (should_cpy)
		{
			if (!(elem->content = (void*)malloc(content_size)))
			{
				free(elem);
				return (NULL);
			}
			elem->content = ft_memcpy(elem->content, content, content_size);
		}
		else
			elem->content = content;
	}
	elem->content_size = content ? content_size : 0;
	elem->next = NULL;
	return (elem);
}

t_list			*ft_lstnew_cpy(void const *content, size_t content_size)
{
	return (ft_lstnew_should_cpy((void*)content, content_size, 1));
}

t_list			*ft_lstnew(void *content, size_t content_size)
{
	return (ft_lstnew_should_cpy(content, content_size, 0));
}
