/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:55 by codk              #+#    #+#             */
/*   Updated: 2025/10/25 07:19:25 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expander_init(t_command **cmd, t_shell *sh)
{
	t_command	*t;

	t = *cmd;
	while (t)
	{
		ft_expander_cmd(t, sh);
		t = t->next;
	}
}

void	ft_expander_cmd(t_command *cmd, t_shell *sh)
{
	t_element	*e;
	int			i;

	i = 1;
	e = cmd->element;
	while (e)
	{
		if (e->kind == ARG)
		{
			ft_expander_arg(e, sh);
			if (i && e->u_.arg->str[0] == '\0' && (e->u_.arg->type == DOLLAR
					|| e->u_.arg->type == SPECIAL_VARIABLE))
			{
				e = ft_expander_empty_var(cmd, e);
				continue ;
			}
			i = 0;
		}
		else if (e->kind == REDIR)
			ft_expander_redir(e, sh);
		e = e->next;
	}
}

void	ft_expander_arg(t_element *lmt, t_shell *sh)
{
	char	*a;
	char	*b;

	if (ft_strchr(lmt->u_.arg->str, '$') && (lmt->u_.arg->type == DOLLAR
			|| lmt->u_.arg->type == SPECIAL_VARIABLE))
	{
		a = lmt->u_.arg->str;
		b = ft_expander_string(sh, a);
		if (b)
		{
			lmt->u_.arg->str = b;
			free(a);
		}
	}
}

void	ft_expander_redir(t_element *lmt, t_shell *sh)
{
	char	*a;
	char	*b;

	if (ft_strchr(lmt->u_.redirs->target, '$')
		&& (lmt->u_.redirs->target_type == DOLLAR
			|| lmt->u_.redirs->target_type == SPECIAL_VARIABLE))
	{
		a = lmt->u_.redirs->target;
		b = ft_expander_string(sh, a);
		if (b)
		{
			lmt->u_.redirs->target = b;
			free(a);
		}
	}
}

char	*ft_expander_string(t_shell *sh, char *s)
{
	t_var_pos	*var;
	char		**val;
	char		*a;
	int			i;

	var = ft_expander_var_pos(s, &i);
	if (!var || i == 0)
		return (ft_strdup(s));
	val = ft_expander_value(sh, var, i);
	if (!val)
		return (ft_free_var(var, NULL, i), NULL);
	a = ft_expander_string_create(s, var, val, i);
	return (ft_free_var(var, val, i), a);
}
