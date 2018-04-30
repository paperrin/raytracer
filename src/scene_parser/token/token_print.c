/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:09:56 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 18:51:42 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/token.h"

void			token_indent(unsigned int indent_depth)
{
	int			i;

	i = -1;
	while (++i < (int)indent_depth)
		ft_putchar('\t');
}

int				token_print(t_token const *const token,
		unsigned int indent_depth)
{
	static void			*f_print_tokens[TOKEN_PRINT_NB_F_TOKENS * 2] = {
		(void*)token_type_punc, (void*)&token_punc_print,
		(void*)token_type_str, (void*)&token_str_print,
		(void*)token_type_num, (void*)&token_num_print,
		(void*)token_type_op, (void*)&token_op_print,
		(void*)token_type_var, (void*)&token_var_print,
		(void*)token_type_call, (void*)&token_call_print};
	int					i;

	i = -1;
	while (token && ++i < TOKEN_PRINT_NB_F_TOKENS)
	{
		if (token->type == (unsigned int)f_print_tokens[i * 2])
		{
			if (!((t_f_token_print*)f_print_tokens[i * 2 + 1])(token,
						indent_depth))
				return (0);
			return (1);
		}
	}
	token_indent(indent_depth);
	ft_putstr(token ? "{unknown token}" : "{null token}");
	return (1);
}
