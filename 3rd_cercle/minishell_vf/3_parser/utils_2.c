/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:19 by codk              #+#    #+#             */
/*   Updated: 2025/10/25 06:51:16 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*ft_parser_create_redir(t_type type, char *s, t_type target_type)
{
	t_redir	*redir;

	if (!s)
		return (NULL);
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->target = ft_strdup(s);
	if (!redir->target)
		return (free(redir), NULL);
	redir->type = type;
	redir->target_type = target_type;
	redir->next = NULL;
	return (redir);
}

t_element	*ft_parser_create_element_arg(t_type t, char *s)
{
	t_element	*lmt;
	t_arg		*arg;

	if (!s)
		return (NULL);
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->str = ft_strdup(s);
	if (!arg->str)
		return (free(arg), NULL);
	arg->type = t;
	lmt = malloc(sizeof(t_element));
	if (!lmt)
	{
		if (arg->str)
			free(arg->str);
		return (free(arg), NULL);
	}
	lmt->kind = ARG;
	lmt->u_.arg = arg;
	lmt->next = NULL;
	return (lmt);
}

int	ft_parser_add_cmd(t_command *cmd, char *s)
{
	if (cmd->cmd == CMD_NONE)
	{
		cmd->cmd = ft_parser_cmd(s);
		return (1);
	}
	return (0);
}

int	ft_parser_add_arg(t_command *cmd, t_type type, char *s)
{
	t_element	*lmt;
	t_element	*t;

	if (!cmd || !s)
		return (0);
	lmt = ft_parser_create_element_arg(type, s);
	if (!lmt)
		return (0);
	if (!cmd->element)
		cmd->element = lmt;
	else
	{
		t = ft_element_last_node(cmd->element);
		t->next = lmt;
	}
	cmd->nb_args++;
	return (1);
}

t_type_cmd	ft_parser_cmd(char *s)
{
	int	i;

	if (!s)
		return (NOT_BUILTIN);
	i = ft_strlen(s);
	if (i == 4 && (ft_strncmp(s, "echo", i) == 0))
		return (T_ECHO);
	if (i == 2 && (ft_strncmp(s, "cd", i) == 0))
		return (T_CD);
	if (i == 3 && (ft_strncmp(s, "pwd", i) == 0))
		return (T_PWD);
	if (i == 6 && (ft_strncmp(s, "export", i) == 0))
		return (T_EXPORT);
	if (i == 5 && (ft_strncmp(s, "unset", i) == 0))
		return (T_UNSET);
	if (i == 3 && (ft_strncmp(s, "env", i) == 0))
		return (T_ENV);
	if (i == 4 && (ft_strncmp(s, "exit", i) == 0))
		return (T_EXIT);
	return (NOT_BUILTIN);
}
