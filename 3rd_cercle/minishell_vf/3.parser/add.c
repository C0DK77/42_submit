/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:19 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 06:43:55 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_cmd(t_command *cmd, char *str)
{
	if (cmd->cmd == CMD_NONE)
	{
		cmd->cmd = ft_parser_add_cmd(str);
		return (1);
	}
	return (0);
}

int	ft_parser_add_arg(t_command *cmd, t_type type, const char *str)
{
	t_element	*element;

	if (!cmd || !str)
		return (0);
	element = create_element_arg(type, str);
	if (!element)
		return (0);
	add_element_to_command(cmd, element);
	cmd->nb_args++;
	return (1);
}

int	ft_parser_add_redir(t_token **tk, t_command **cmd)
{
	t_token		*redir;
	t_token		*t;
	t_element	*element;

	if (!tk || !*tk || !cmd || !*cmd)
		return (0);
	redir = *tk;
	t = redir->next;
	if (!t)
		return (0);
	element = create_element_redir(redir->type, t->str, t->type);
	if (!element)
		return (0);
	add_element_to_command(*cmd, element);
	*tk = t->next;
	return (1);
}

int	ft_parser_handle_pipe(t_token **tk, t_command **cmd)
{
	t_command	*t;

	t = NULL;
	if ((*tk)->type == PIPE)
	{
		t = create_new_command();
		if (!t)
			return (ft_putstr_fd(2, "minishell: EXIT FAILURE \n"), 0);
		(*cmd)->has_pipe_out = 1;
		(*cmd)->next = t;
		t->previous = *cmd;
		(*cmd) = t;
		*tk = (*tk)->next;
		return (1);
	}
	return (0);
}

int	handle_cmd_or_arg(t_token **tk, t_command **cmd)
{
	t_type_cmd	b;

	if ((*cmd)->cmd == CMD_NONE)
	{
		b = ft_parser_add_cmd((*tk)->str);
		(*cmd)->cmd = b;
	}
	if (!ft_parser_add_arg(*cmd, (*tk)->type, (*tk)->str))
		return (0);
	*tk = (*tk)->next;
	return (1);
}
