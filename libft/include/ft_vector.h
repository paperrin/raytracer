/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 19:50:27 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/16 19:20:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <stdlib.h>
# include "ft_math.h"

# define FT_VECTOR_BASE_GROW_FACTOR 2

# define VECTOR_PUSHR(V, R) ft_vector_push_back(&V, (char*)R)
# define VECTOR_PUSH(V, T, P) (P = (T*)ft_vector_push_back(&V, NULL))

# define VECTOR_PUSHR_FRONT(V, R) ft_vector_push_front(&V, (char*)R)
# define VECTOR_PUSH_FRONT(V, T, P) (P = (T*)ft_vector_push_front(&V, NULL))

typedef struct	s_vector
{
	char		*begin;
	char		*end;
	size_t		data_size;
	size_t		reserve;
	int			(*f_copy)(char*, char*);
	void		(*f_free)(char*);
}				t_vector;

/*
** vector/ft_vector.c
*/
t_vector		ft_vector_create(size_t data_size, int (*f_copy)(char*, char*),
		void (*f_free)(char*));
void			ft_vector_destroy(t_vector *vector);

/*
** vector/ft_vector_info.c
*/
size_t			ft_vector_size(t_vector const *const vector);
size_t			ft_vector_size_bytes(t_vector const *const vector);
size_t			ft_vector_capacity(t_vector const *const vector);
size_t			ft_vector_capacity_bytes(t_vector const *const vector);

/*
** vector/ft_vector_resize.c
*/
char			*ft_vector_reserve(t_vector *vector, size_t reserve);
char			*ft_vector_reserve_it(t_vector *vector, size_t reserve,
		char **it);
char			*ft_vector_shrink_to_fit(t_vector *vector);

/*
** vector/ft_vector_insert.c
*/
char			*ft_vector_pinsert(t_vector *vector, char *place,
		char const *const elem);
char			*ft_vector_insert(t_vector *vector, size_t index,
		char const *const elem);
char			*ft_vector_push_front(t_vector *vector,
		char const *const elem);
char			*ft_vector_push_back(t_vector *vector,
		char const *const elem);

/*
** vector/ft_vector_at.c
*/
char			*ft_vector_at(t_vector const *const vector, size_t index);
char			*ft_vector_begin(t_vector const *const vector);
char			*ft_vector_end(t_vector const *const vector);

/*
** vector/ft_vector_pop_at.c
*/
char			*ft_vector_pop_at(t_vector *vector, size_t index,
		char *ret_value);
char			*ft_vector_pop_front(t_vector *vector, char *ret_value);
char			*ft_vector_pop_back(t_vector *vector, char *ret_value);

/*
** vector/ft_vector_erase.c
*/
char			*ft_vector_perase_n(t_vector *vector, char *elem_first,
		size_t n);
char			*ft_vector_erase_n(t_vector *vector, size_t index, size_t n);
char			*ft_vector_perase(t_vector *vector, char *elem);
char			*ft_vector_erase(t_vector *vector, size_t index);
void			ft_vector_clear(t_vector *vector);

#endif
