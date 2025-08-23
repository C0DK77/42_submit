/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:20:41 by ecid              #+#    #+#             */
/*   Updated: 2025/08/23 20:18:52 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **s, t_envp **l)
{
	int status;

	if (!s || !s[1])
		return (ft_export_no_arguments(l));   // <-- pas d’arguments
	status = 0;
	s++;                                      // <-- skip "export"
	while (*s)
	{
		if (!ft_export_arguments(s, l, NULL))
			status = 1;                       // on continue mais on note l'erreur
		s++;
	}
	return (status);
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
	int		append;   // 1 si +=
	int		name_len; // longueur du nom
	char	*t;
	char	*name;

	append = 0;
	name_len = 0;
	t = *s;
	if (!ft_export_check_valid_var(t, &name_len))
		return (ft_export_error(t));
	if (t[name_len] == '+' && t[name_len + 1] == '=')
	{
		append = 1;
		a = t + name_len + 2;
	}
	else if (t[name_len] == '=')
		a = t + name_len + 1;
	else
		a = NULL;
	name = ft_strndup(t, name_len);            // <-- corrige: j, pas i
	if (!name)
		return (0);
	/* ft_export_check_value prend la propriété de name (elle le free) */
	if (!ft_export_check_value(l, name, a, append))
		return (0);
	return (1);
}

int	ft_export_check_valid_var(char *s, int *i)
{
	char	*t;

	if (!s || (!ft_isalpha((unsigned char)s[0]) && s[0] != '_'))
		return (0);
	t = s + 1;
	while (*t && (ft_isalnum((unsigned char)*t) || *t == '_'))
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
