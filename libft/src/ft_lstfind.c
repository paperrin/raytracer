/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 20:16:20 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/09 11:37:39 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstfind(t_list *list, void *cmp_data
		, t_list *(*cmp_f)(t_list*, void*))
{
	t_list	*ret;

	if (!list || !cmp_f)
		return (NULL);
	ret = NULL;
	while (list)
	{
		ret = (*cmp_f)(list, cmp_data);
		if (ret)
			return (ret);
		list = list->next;
	}
	return (NULL);
}
