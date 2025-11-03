/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:42:59 by codk              #+#    #+#             */
/*   Updated: 2025/10/28 10:27:12 by corentindes      ###   ########.fr       */
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
			ft_free_element(t->element);
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
		ft_free_all(2, tk->str, tk);
		tk = t;
	}
}
