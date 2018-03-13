/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:23:37 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/11 17:55:19 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

void		token_destroy(t_token **token)
{
	static void		*f_token_type_destroy[TOKEN_DESTROY_NB_F_TOKENS * 2] = {
		(void*)token_type_punc, (void*)&token_punc_destroy,
		(void*)token_type_num, (void*)&token_num_destroy,
		(void*)token_type_str, (void*)&token_str_destroy,
		(void*)token_type_kw, (void*)&token_kw_destroy,
		(void*)token_type_var, (void*)&token_var_destroy,
		(void*)token_type_op, (void*)&token_op_destroy,
		(void*)token_type_call, (void*)&token_call_destroy,
		(void*)token_type_bool, (void*)&token_bool_destroy};
	int				i;

	i = -1;
	while (i < TOKEN_DESTROY_NB_F_TOKENS)
	{
		if ((*token)->type == (unsigned int)f_token_type_destroy[i * 2])
		{
			((t_f_token_destroy*)f_token_type_destroy[i * 2 + 1])(*token);
			ft_memdel((void**)token);
			return ;
		}
	}
	error_string("token_destroy(): unknown token type");
}
