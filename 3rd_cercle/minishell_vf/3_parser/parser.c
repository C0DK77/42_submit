/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:37 by codk              #+#    #+#             */
/*   Updated: 2025/10/26 17:53:22 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*ft_parser_init(t_token *t)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd = CMD_NONE;
	if (!ft_parser_redir(t) || !ft_parser_pipe(t))
		return (ft_free_cmd(cmd), NULL);
	if (!ft_parser_save(cmd, t))
		return (ft_free_cmd(cmd), NULL);
	return (cmd);
}

int	ft_parser_redir(t_token *tk)
{
	t_token	*t;

	t = tk;
	while (t)
	{
		if (!(t->type == HEREDOC || t->type == APPEND || t->type == REDIR_IN
				|| t->type == REDIR_OUT))
		{
			t = t->next;
			continue ;
		}
		if (!ft_parser_valid_redir(t, &t))
			return (0);
	}
	return (1);
}

int	ft_parser_pipe(t_token *tk)
{
	t_token	*t;
	t_token	*target;

	t = tk;
	if (!t)
		return (1);
	if (t->type == PIPE)
		return (ft_putstr_fd(SYNTAX "'|'\n", 2), 0);
	while (t)
	{
		target = t->next;
		if (t->type == PIPE && (!target || target->type == PIPE))
			return (ft_putstr_fd(SYNTAX "'|'\n", 2), 0);
		t = target;
	}
	return (1);
}

int	ft_parser_save(t_command *cmd, t_token *tk)
{
	int			i;
	t_command	*t;

	t = cmd;
	while (tk)
	{
		i = ft_parser_special_tokens(&tk, &t);
		if (i == 0)
			return (0);
		if (i == 1)
			continue ;
		if (!ft_parser_add_arg(t, tk->type, tk->str))
			return (0);
		tk = tk->next;
	}
	return (1);
}

int	ft_parser_valid_redir(t_token *tk, t_token **next)
{
	t_token	*t;

	t = tk->next;
	if (!t)
		return (ft_putstr_fd(SYNTAX "`newline'\n", 2), 0);
	if (!(t->type == LITERAL || t->type == DOLLAR
			|| t->type == SPECIAL_VARIABLE))
	{
		if (t->str && t->str[0])
			ft_putall_fd(2, 3, SYNTAX "`", t->str, "'\n");
		else
			ft_putstr_fd(SYNTAX "`newline'\n", 2);
		return (0);
	}
	*next = t->next;
	return (1);
}
