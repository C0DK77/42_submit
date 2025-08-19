/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:03:07 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/19 18:43:07 by ecid             ###   ########.fr       */
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
		perror("getcwd");
		p = malloc(ft_strlen("minishell > ") + 1);
		if (!p)
			return (NULL);
		ft_strcpy(p, "minishell > ");
		return (p);
	}
	p = malloc(ft_strlen(c) + 4);
	if (!p)
	{
		free(c);
		return (NULL);
	}
	ft_strcpy(p, c);
	p[ft_strlen(c)] = ' ';
	p[ft_strlen(c) + 1] = '>';
	p[ft_strlen(c) + 2] = ' ';
	p[ft_strlen(c) + 3] = '\0';
	free(c);//ajout ici
	return (p);
}

t_envp	*ft_env_copy(char *s)
{
	char	*a;
	t_envp	*n;

	n = malloc(sizeof(t_envp));
	if (!n)
		return (NULL);
	a = ft_strchr(s, '=');
	if (!a)
	{
		free(n);
		return (NULL);
	}
	n->var = ft_strndup(s, a - s);
	n->value = ft_strdup(a + 1);
	n->next = NULL;
	if (!n->var || !n->value)
	{
		free(n->var);
		free(n->value);
		free(n);
		return (NULL);
	}
	return (n);
}

t_envp	*ft_env_init(char **l)
{
	t_envp	*head;
	t_envp	*tail;
	t_envp	*n;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (l[i])
	{
		n = ft_env_copy(l[i]);
		if (!n)
			return (NULL);
		if (!head)
		{
			head = n;
			tail = n;
		}
		else
		{
			tail->next = n;
			tail = n;
		}
		i++;
	}
	return (head);
}

char	*ft_env_search_value(t_envp *l, char *v)
{
	while (l)
	{
		if (ft_strcmp(l->var, v) == 0)
			return (l->value);
		l = l->next;
	}
	return (NULL);
}

t_envp	*ft_env_search_node(t_envp *l, char *v)
{
	while (l)
	{
		if (ft_strcmp(l->var, v) == 0)
			return (l);
		l = l->next;
	}
	return (NULL);
}

void	ft_env_free(t_envp *l)
{
	t_envp	*t;

	while (l)
	{
		t = l->next;
		free(l->var);
		free(l->value);
		free(l);
		l = t;
	}
}
