/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:51:45 by ecid              #+#    #+#             */
/*   Updated: 2025/09/28 23:47:37 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_id_err(const char *name)
{
	char	*msg;

	msg = ft_strjoin_three("minishell: unset: `", (char *)name,
			"': not a valid identifier\n");
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		free(msg);
	}
	else
		write(STDERR_FILENO, "minishell: unset: not a valid identifier\n", 41);
}

static int	is_valid_identifier(const char *t)
{
	if (!t || (!ft_isalpha((unsigned char)t[0]) && t[0] != '_'))
		return (0);
	t++;
	while (*t)
	{
		if (!(ft_isalnum((unsigned char)*t) || *t == '_'))
			return (0);
		t++;
	}
	return (1);
}

int	ft_unset_check_identifier(char **s)
{
	if (is_valid_identifier(*s))
		return (1);
	unset_id_err(*s);
	return (0);
}

int	ft_unset_error(int i, char *s)
{
	char	*error_msg;

	g_exit_status = 1;
	if (i == 0)
	{
		error_msg = ft_strjoin_three("minishell: unset: `", s,
				"': invalid option\n");
		if (error_msg)
		{
			write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
			free(error_msg);
		}
		else
		{
			write(STDERR_FILENO, "minishell: unset: invalid option\n", 33);
		}
		write(STDERR_FILENO, "unset: usage: unset name [name ...]\n", 36);
		g_exit_status = 2;
	}
	return (g_exit_status);
}

void	ft_unset_change(char **s, t_envp **l)
{
	t_envp	*current;
	t_envp	*prev;
	char	*var_to_unset;

	var_to_unset = *s;
	current = *l;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->var, var_to_unset) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*l = current->next;
			free(current->var);
			if (current->value)
				free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}
