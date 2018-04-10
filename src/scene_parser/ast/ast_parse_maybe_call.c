/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_maybe_call.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:25:53 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 00:22:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/ast.h"

static int				add_arg(t_token **tk_call, t_token **tk_arg)
{
	t_token		**args;
	int			i;

	args = (*tk_call)->as.call.args;
	(*tk_call)->as.call.args = (t_token**)malloc(sizeof(t_token*)
			* ((*tk_call)->as.call.args_len + 1));
	i = -1;
	if (!(*tk_call)->as.call.args)
	{
		token_destroy(tk_call);
		return (0);
	}
	while (++i < (*tk_call)->as.call.args_len)
		(*tk_call)->as.call.args[i] = args[i];
	ft_memdel((void**)&args);
	(*tk_call)->as.call.args[(*tk_call)->as.call.args_len] = *tk_arg;
	(*tk_call)->as.call.args_len++;
	return (1);
}

static int				parse_args(t_token_stream *const tkstream,
		t_token **tk_call)
{
	t_token		*tk;
	t_token		*tk_arg;

	while ((tk = tkstream_peek(tkstream)))
	{
		if (tk->type == token_type_punc && tk->as.punc.value == ')')
			break ;
		if (!(tk_arg = ast_parse_expr(tkstream)) || !add_arg(tk_call, &tk_arg)
				|| !(tk = tkstream_peek(tkstream)))
			return (0);
		if (tk->type == token_type_punc && tk->as.punc.value == ',')
			token_destroy(&tk);
		else
			break ;
		tkstream_next(tkstream);
	}
	if (tk->type != token_type_punc && tk->as.punc.value != ')')
	{
		token_destroy(&tk);
		if (tk_call)
			token_destroy(tk_call);
		return (tkstream_error(tkstream, "unexpected token in function call"));
	}
	token_destroy(&tkstream->cur);
	return (1);
}

static t_token			*parse_call(t_token_stream *const tkstream,
		t_token *tk_var)
{
	t_token		*tk_call;

	if (!(tk_call = (t_token*)malloc(sizeof(*tk_call))))
	{
		token_destroy(&tk_var);
		return (perror_string(ERR_MEMORY));
	}
	tk_call->type = token_type_call;
	tk_call->as.call.func = tk_var->as.var.name;
	tk_call->as.call.args = NULL;
	tk_call->as.call.args_len = 0;
	ft_memdel((void**)&tk_var);
	if (!parse_args(tkstream, &tk_call))
		return (NULL);
	tkstream_next(tkstream);
	return (tk_call);
}

t_token					*ast_parse_maybe_call(t_token_stream *const tkstream)
{
	t_token		*tk_maybe_call;
	t_token		*tk;

	if (!(tk_maybe_call = tkstream_peek(tkstream)))
		return (NULL);
	if (!(tk = tkstream_next(tkstream)))
	{
		if (cstream_peek(tkstream->cstream) == 0)
			return (tk_maybe_call);
		token_destroy(&tk_maybe_call);
		return (NULL);
	}
	if (tk->type == token_type_punc && tk->as.punc.value == '(')
	{
		token_destroy(&tk);
		if (tkstream_next(tkstream))
			return (parse_call(tkstream, tk_maybe_call));
		token_destroy(&tk_maybe_call);
		return (NULL);
	}
	return (tk_maybe_call);
}
