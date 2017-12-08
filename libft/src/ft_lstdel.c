/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 20:16:38 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/13 16:26:23 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*cur;
	t_list	*next;

	cur = *alst;
	while (cur)
	{
		next = cur->next;
		ft_lstdelone(&cur, del);
		cur = next;
	}
	*alst = NULL;
}
