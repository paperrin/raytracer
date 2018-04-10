/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:56:49 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 17:04:36 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/token.h"

int			token_dup(t_token const *const src, t_token *const dst)
{
	static void const *const	f_token_dup[TOKEN_DUP_NB_F_TOKENS * 2] = {
		(void*)token_type_punc, (void*)&token_punc_dup,
		(void*)token_type_num, (void*)&token_num,
		(void*)token_type_str, (void*)&token_str,
		(void*)token_type_var, (void*)&token_var,
		(void*)token_type_op, (void*)&token_op,
		(void*)token_type_call, (void*)&token_call};
	int		i;

	i = -1;
	while (++i < TOKEN_DUP_NB_F_TOKENS)
	{
		if (src->type != (t_e_token_type)f_token_dup[i * 2])
			continue ;
		if (!((t_f_token_dup*)f_token_dup[i * 2 + 1])(src, dst))
			return (0);
		return (1);
	}
	*dst = *src;
	return (1);
}
