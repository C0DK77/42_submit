/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:43:17 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/26 15:52:59 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_unset(char **s, t_envp **l)
{
	while (*s && s)
	{
		if ((*s)[0] == '-' && (*s)[1] != '\0')
			return (ft_unset_error(0, *s));
		if (!ft_unset_check_identifier(*s))
		{
			s++;
			continue ;
		}
		ft_unset_change(s, l);
		s++;
	}
	g_exit_status = 0;
	return (g_exit_status);
}

int	ft_unset_check_identifier(char *s)
{
	int	i;

	if (ft_strchr(s, '='))
		return (0);
	if (!(ft_isalpha((unsigned char)s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset_change(char **s, t_envp **l)
{
	t_envp	*t;
	t_envp	*p;

	t = *l;
	p = NULL;
	while (t)
	{
		if (ft_strcmp(t->var, *s) == 0)
		{
			if (p)
				p->next = t->next;
			else
				*l = t->next;
			free(t->var);
			if (t->value)
				free(t->value);
			free(t);
			break ;
		}
		p = t;
		t = t->next;
	}
}

int	ft_unset_error(int i, char *s)
{
	if (i == 0)
	{
		g_exit_status = 2;
		return (ft_putall_fd(2, 3, "minishell: unset: ", s,
				": invalid option\nunset: usage: unset name [name ...]\n"), 2);
	}
	return (1);
}
