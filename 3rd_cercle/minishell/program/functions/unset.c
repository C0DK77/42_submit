/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:43:17 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/19 03:07:39 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_unset(char **s, t_envp **l)
{
	int	i;

	i = 0;
	while (*s && s)
	{
		if ((*s)[0] == '-' && (*s)[1] != '\0')
			return (ft_unset_error(0, *s));
		if (!ft_unset_check_identifier(s))
		{
			i = 1;
			s++;
			continue ;
		}
		ft_unset_change(s, l);
		s++;
	}
	if (i)
		g_exit_status = 1;
	else
		g_exit_status = 0;
	return (g_exit_status);
}

int	ft_unset_check_identifier(char **s)
{
	int		i;
	char	*t;

	t = *s;
	if (!(ft_isalpha((unsigned char)t[0]) || t[0] == '_'))
	{
		fprintf(stderr, "minishell: unset: `%s': not a valid identifier\n", *s);
		return (0);
	}
	i = 1;
	while (t[i])
	{
		if (!(ft_isalnum((unsigned char)t[i]) || t[i] == '_'))
		{
			fprintf(stderr, "minishell: unset: `%s': not a valid identifier\n",
				*s);
			return (0);
		}
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
		fprintf(stderr, "minishell: unset: %s: invalid option\n", s);
		fprintf(stderr, "unset: usage: unset name [name ...]\n");
		g_exit_status = 2;
		return (2);
	}
	return (1);
}
