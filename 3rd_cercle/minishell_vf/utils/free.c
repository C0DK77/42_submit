/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:43:19 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 19:28:43 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_free_program(t_character *ch, t_token *tk, t_command *cmd, int i)
{
	if (cmd)
		ft_free_cmd(cmd);
	if (tk)
		ft_free_token(tk);
	if (ch)
		ft_free_char(ch);
	return (i);
}

void	ft_free_cmd(t_command *cmd)
{
	t_command	*t;
	t_command	*next;

	t = cmd;
	while (t)
	{
		next = t->next;
		if (t->element)
			free_element_list(t->element);
		free(t);
		t = next;
	}
}

void	ft_free_env(t_shell *sh)
{
	size_t	i;

	if (!sh || !sh->env)
		return ;
	i = 0;
	while (sh->env[i] != NULL)
		free(sh->env[i++]);
	free(sh->env);
	sh->env = NULL;
}

void	ft_free_char(t_character *ch)
{
	t_character	*t;

	while (ch)
	{
		t = ch->next;
		free(ch);
		ch = t;
	}
}

void	ft_free_token(t_token *tk)
{
	t_token	*t;

	while (tk)
	{
		t = tk->next;
		ft_free_all(tk->str, tk);
		tk = t;
	}
}

static void	free_redir(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		if (current->target)
			free(current->target);
		free(current);
		current = next;
	}
}

void	free_element_list(t_element *element)
{
	t_element	*current;
	t_element	*next;

	current = element;
	while (current)
	{
		next = current->next;
		if (current->kind == ARG)
		{
			if (current->u_.arg)
			{
				if (current->u_.arg->str)
					free(current->u_.arg->str);
				free(current->u_.arg);
			}
		}
		else if (current->kind == REDIR)
		{
			if (current->u_.redirs)
				free_redir(current->u_.redirs);
		}
		free(current);
		current = next;
	}
}

void	cleanall(t_character *ch, t_token *tk, t_command *cmd)
{
	ft_free_all(ch, tk, cmd);
}
