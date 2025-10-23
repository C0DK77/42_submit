/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:43 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 06:42:46 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_element	*lst_last_node(t_element *lmt)
{
	t_element	*t;

	t = lmt;
	if (!t)
		return (NULL);
	while (t->next)
		t = t->next;
	return (t);
}

int	is_operator(t_type type)
{
	if (type == PIPE || type == REDIR_IN || type == HEREDOC || type == REDIR_OUT
		|| type == APPEND || type == DOLLAR || type == SPECIAL_VARIABLE)
		return (1);
	return (0);
}

int	is_command(t_type_cmd type)
{
	if (type == T_ECHO || type == T_CD || type == T_PWD || type == T_EXPORT
		|| type == T_UNSET || type == T_ENV || type == T_EXIT)
		return (1);
	return (0);
}

t_type_cmd	ft_parser_add_cmd(char *s)
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
