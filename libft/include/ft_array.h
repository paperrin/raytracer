/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:29:53 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/10 22:57:48 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARRAY_H
# define FT_ARRAY_H

# include <stdlib.h>
# include "libft.h"
# include "ft_math.h"

typedef void**		t_array_it;

typedef struct		s_array
{
	void		**data;
	t_array_it	begin;
	t_array_it	end;
	void		(*f_free)(void**);
	size_t		size;
	size_t		reserve_front;
	size_t		reserve_back;
}					t_array;

t_array				ft_array_init(void (*f_free)(void**));
void				ft_array_free(t_array *array);

t_array_it			ft_array_add(t_array *array, size_t index, void *elem);

t_array_it			ft_array_push_front(t_array *array, void *data);
t_array_it			ft_array_push_back(t_array *array, void *data);

void				*ft_array_front(t_array *array);
void				*ft_array_back(t_array *array);

void				*ft_array_pop(t_array *array, size_t index);
void				*ft_array_pop_front(t_array *array);
void				*ft_array_pop_back(t_array *array);

t_array_it			ft_array_sort(t_array *array, int f_cmp(void*, void*));

t_array_it			ft_array_reserve(t_array *array
						, size_t reserve_front, size_t reserve_back);

#endif
