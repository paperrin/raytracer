/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 19:50:27 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/20 22:33:09 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <stdlib.h>
# include "ft_math.h"

# define FT_VECTOR_BASE_GROW_FACTOR 2

typedef struct	s_vector
{
	void		*begin;
	void		*end;
	size_t		data_size;
	size_t		reserve;
	int			(*f_cmp)(void*, void*);
	int			(*f_copy)(void*, void*);
	void		(*f_free)(void*);
}				t_vector;

/*
** vector/ft_vector.c
*/
t_vector		ft_vector_create(size_t data_size, int (*f_copy)(void*, void*),
		void (*f_free)(void*));
void			ft_vector_destroy(t_vector *vector);

/*
** vector/ft_vector_info.c
*/
size_t			ft_vector_size(t_vector const *const vector);
size_t			ft_vector_size_bytes(t_vector const *const vector);
size_t			ft_vector_capacity(t_vector const *const vector);
size_t			ft_vector_capacity_bytes(t_vector const *const vector);
int				ft_vector_empty(t_vector const *const vector);

/*
** vector/ft_vector_resize.c
*/
void			*ft_vector_reserve(t_vector *vector, size_t reserve);
void			*ft_vector_reserve_it(t_vector *vector, size_t reserve,
		void **it);
void			*ft_vector_shrink_to_fit(t_vector *vector);

/*
** vector/ft_vector_insert.c
*/
void			*ft_vector_pinsert(t_vector *vector, void *place,
		void const *const elem);
void			*ft_vector_insert(t_vector *vector, size_t index,
		void const *const elem);
void			*ft_vector_push_front(t_vector *vector,
		void const *const elem);
void			*ft_vector_push_back(t_vector *vector,
		void const *const elem);

/*
** vector/ft_vector_at.c
*/
void			*ft_vector_at(t_vector const *const vector, size_t index);
void			*ft_vector_front(t_vector const *const vector);
void			*ft_vector_back(t_vector const *const vector);
void			*ft_vector_begin(t_vector const *const vector);
void			*ft_vector_end(t_vector const *const vector);

/*
** vector/ft_vector_pop_at.c
*/
void			*ft_vector_pop_at(t_vector *vector, size_t index,
		void *ret_value);
void			*ft_vector_pop_front(t_vector *vector, void *ret_value);
void			*ft_vector_pop_back(t_vector *vector, void *ret_value);

/*
** vector/ft_vector_erase.c
*/
void			*ft_vector_perase_n(t_vector *vector, void *elem_first,
		size_t n);
void			*ft_vector_erase_n(t_vector *vector, size_t index, size_t n);
void			*ft_vector_perase(t_vector *vector, void *elem);
void			*ft_vector_erase(t_vector *vector, size_t index);
void			ft_vector_clear(t_vector *vector);

#endif
