/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prompt_and_list_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:03:07 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/28 20:45:07 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_prompt(void)
{
	char	*p;
	char	*c;

	c = getcwd(NULL, 0);
	if (!c)
	{
		p = malloc(ft_strlen("minishell > ") + 1);
		if (!p)
			return (NULL);
		ft_strcpy(p, "minishell > ");
		return (p);
	}
	p = malloc((sizeof("minishell ") - 1) + ft_strlen(c) + (sizeof(" > ") - 1)
			+ 1);
	if (!p)
		return (free(c), NULL);
	ft_strcpy(p, "minishell ");
	ft_strcpy(p + (sizeof("minishell ") - 1), c);
	ft_strcpy(p + (sizeof("minishell ") - 1) + ft_strlen(c), " > ");
	free(c);
	return (p);
}

int	append_env_push_back(t_envp **first, t_envp **last, t_envp *n)
{
	if (!n)
		return (0);
	if (!*first)
	{
		*first = n;
		*last = n;
	}
	else
	{
		(*last)->next = n;
		*last = n;
	}
	return (1);
}

t_envp	*ft_env_list_init(char **l)
{
	t_envp	*first;
	t_envp	*last;
	t_envp	*n;
	int		i;

	first = NULL;
	last = NULL;
	i = 0;
	while (l[i])
	{
		n = ft_env_var_copy(l[i]);
		if (!append_env_push_back(&first, &last, n))
			return (NULL);
		i++;
	}
	return (first);
}

t_envp	*ft_env_var_copy(char *s)
{
	char	*a;
	t_envp	*n;

	n = malloc(sizeof(t_envp));
	if (!n)
		return (NULL);
	n->var = NULL;
	n->value = NULL;
	n->next = NULL;
	n->export = 1;
	a = ft_strchr(s, '=');
	if (!a)
	{
		free(n);
		return (NULL);
	}
	n->var = ft_strndup(s, a - s);
	if (!n->var)
	{
		free(n);
		return (NULL);
	}
	n->value = ft_strdup(a + 1);
	if (!n->value)
	{
		free(n->var);
		free(n);
		return (NULL);
	}
	return (n);
}
