/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:37 by codk              #+#    #+#             */
/*   Updated: 2025/10/15 20:51:20 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	validate_redir_target(t_token *redir, t_token **next)
{
	t_token	*target;

	target = redir->next;
	if (!target)
	{
		print_error("syntax error near unexpected token `newline'");
		return (0);
	}
	if (!(target->type == LITERAL || target->type == DOLLAR
			|| target->type == SPECIAL_VARIABLE))
	{
		if (target->str && target->str[0])
			print_syntax_error(target->str);
		else
			print_error("syntax error near unexpected token `newline'");
		return (0);
	}
	*next = target->next;
	return (1);
}

static int	check_redir(t_token *token_list)
{
	t_token	*tkn;

	tkn = token_list;
	while (tkn)
	{
		if (!is_redir(tkn->type))
		{
			tkn = tkn->next;
			continue ;
		}
		if (!validate_redir_target(tkn, &tkn))
			return (0);
	}
	return (1);
}

static int	check_pipe(t_token *token_list)
{
	t_token	*tkn;
	t_token	*target;

	tkn = token_list;
	if (!tkn)
		return (1);
	if (tkn->type == PIPE)
		return (print_error("syntax error near unexpected token '|'"), 0);
	while (tkn)
	{
		target = tkn->next;
		if (tkn->type == PIPE)
		{
			if (!target || target->type == PIPE)
				return (print_error("syntax error near unexpected token '|'"),
					0);
		}
		tkn = target;
	}
	return (1);
}

int	parse_token(t_token *token_list)
{
	if (!check_redir(token_list))
		return (0);
	if (!check_pipe(token_list))
		return (0);
	return (1);
}
