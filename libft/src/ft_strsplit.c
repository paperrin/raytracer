/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 12:08:46 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/03 22:41:58 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		**alloc_tab(char const *s, char c)
{
	size_t	word_count;
	char	**tab;
	int		i;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			word_count++;
		while (s[i] && s[i] != c)
			i++;
	}
	tab = (char**)malloc(sizeof(char*) * (word_count + 1));
	return (tab);
}

char			**ft_strsplit_free(char **tab)
{
	int		tab_i;

	tab_i = 0;
	if (tab)
	{
		while (tab[tab_i])
		{
			if (tab[tab_i])
				free(tab[tab_i++]);
		}
		free(tab);
	}
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	tab_i;
	size_t	i;

	if (!s || !(tab = alloc_tab(s, c)))
		return (NULL);
	tab_i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		if (i == 0)
			break ;
		tab[tab_i] = ft_strsub(s, 0, i);
		if (!tab[tab_i])
			return (ft_strsplit_free(tab));
		tab_i++;
		s += i;
	}
	tab[tab_i] = NULL;
	return (tab);
}
