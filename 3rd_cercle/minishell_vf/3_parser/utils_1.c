/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:31 by codk              #+#    #+#             */
/*   Updated: 2025/10/26 20:31:40 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser_special_tokens(t_token **tk, t_command **cmd)
{
	if ((*tk)->type == HEREDOC || (*tk)->type == APPEND
		|| (*tk)->type == REDIR_IN || (*tk)->type == REDIR_OUT)
		return (ft_parser_add_redir(tk, cmd));
	if ((*tk)->type == LITERAL || (*tk)->type == DOLLAR
		|| (*tk)->type == SPECIAL_VARIABLE)
		return (ft_parser_handle_cmd_or_arg(tk, cmd));
	if ((*tk)->type == PIPE)
		return (ft_parser_handle_pipe(tk, cmd));
	return (-1);
}

int	ft_parser_add_redir(t_token **tk, t_command **cmd)
{
	t_token		*redir;
	t_token		*t;
	t_element	*lmt;
	t_element	*lmt_b;

	if (!tk || !*tk || !cmd || !*cmd)
		return (0);
	redir = *tk;
	t = redir->next;
	if (!t)
		return (0);
	lmt = ft_parser_create_element_redir(redir->type, t->str, t->type);
	if (!lmt)
		return (0);
	if (!(*cmd)->element)
		(*cmd)->element = lmt;
	else
	{
		lmt_b = ft_element_last_node((*cmd)->element);
		lmt_b->next = lmt;
	}
	*tk = t->next;
	return (1);
}

int	ft_parser_handle_pipe(t_token **tk, t_command **cmd)
{
	t_command	*t;

	t = NULL;
	if ((*tk)->type == PIPE)
	{
		t = ft_calloc(1, sizeof(t_command));
		if (!t)
			return (0);
		t->cmd = CMD_NONE;
		if (!t)
			return (ft_putstr_fd("minishell: EXIT FAILURE \n", 2), 0);
		(*cmd)->has_pipe_out = 1;
		(*cmd)->next = t;
		t->previous = *cmd;
		(*cmd) = t;
		*tk = (*tk)->next;
		return (1);
	}
	return (0);
}

int	ft_parser_handle_cmd_or_arg(t_token **tk, t_command **cmd)
{
	t_type_cmd	b;

	if ((*cmd)->cmd == CMD_NONE)
	{
		b = ft_parser_cmd((*tk)->str);
		(*cmd)->cmd = b;
	}
	if (!ft_parser_add_arg(*cmd, (*tk)->type, (*tk)->str))
		return (0);
	*tk = (*tk)->next;
	return (1);
}

t_element	*ft_parser_create_element_redir(t_type type, char *s, t_type target)
{
	t_element	*lmt;
	t_redir		*t;

	if (type == HEREDOC && target == DOLLAR)
		t = ft_parser_create_redir(type, s, LITERAL);
	else
		t = ft_parser_create_redir(type, s, target);
	if (!t)
		return (NULL);
	lmt = malloc(sizeof(t_element));
	if (!lmt)
	{
		if (t->target)
			free(t->target);
		return (free(t), NULL);
	}
	lmt->kind = REDIR;
	lmt->u_.redirs = t;
	lmt->next = NULL;
	return (lmt);
}
