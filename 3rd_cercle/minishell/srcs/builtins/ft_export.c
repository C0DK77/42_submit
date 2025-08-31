/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:20:41 by ecid              #+#    #+#             */
/*   Updated: 2025/08/31 14:34:37 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **s, t_envp **l)
{
	if (!s || !*s)
		return (ft_export_no_arguments(l));
	while (*s)
	{
		if (!ft_export_arguments(s, l, NULL))
			return (1);
		s++;
	}
	return (0);
}

int	ft_export_no_arguments(t_envp **l)
{
	t_envp	*t;

	t = *l;
	while (t)
	{
		if (t->export)
		{
			if (t->value)
				printf("declare -x %s=\"%s\"\n", t->var, t->value);
			else
				printf("declare -x %s\n", t->var);
		}
		t = t->next;
	}
	return (0);
}

int	ft_export_arguments(char **s, t_envp **l, char *a)
{
	int		i;
	int		j;
	char	*t;
	char	*n;

	i = 0;
	j = 0;
	t = *s;
	if (!ft_export_check_valid_var(t, &j))
		return (ft_export_error(t));
	if (t[j] == '+' && t[j + 1] == '=')
	{
		i = 1;
		a = t + j + 2;
	}
	else if (t[j] == '=')
		a = t + j + 1;
	else
		a = NULL;
	n = ft_strndup(t, j);
	if (!n || !ft_export_check_value(l, n, a, i))
		return (0);
	return (1);
}

int	ft_export_check_valid_var(char *s, int *i)
{
	char	*t;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	t = s + 1;
	while (*t && (ft_isalnum(*t) || *t == '_'))
		t++;
	if (*t == '\0' || *t == '=' || (*t == '+' && *(t + 1) == '='))
	{
		*i = (int)(t - s);
		return (1);
	}
	return (0);
}

int	ft_export_error(char *t)
{
	return (ft_putstr_fd("minishell: export: `", 2), ft_putstr_fd(t, 2),
		ft_putstr_fd("': not a valid identifier\n", 2), 0);
}
