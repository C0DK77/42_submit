/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prompt_and_list_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:31:50 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/22 17:48:41 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
		return (free(c), NULL);
	ft_strcpy(p, c);
	p[ft_strlen(c)] = ' ';
	p[ft_strlen(c) + 1] = '>';
	p[ft_strlen(c) + 2] = ' ';
	p[ft_strlen(c) + 3] = '\0';
	return (p);
}

t_envp	*ft_env_list_init(char **l)
{
	t_envp	*first_n;
	t_envp	*last_n;
	t_envp	*n;
	int		i;

	first_n = NULL;
	last_n = NULL;
	i = 0;
	while (l[i])
	{
		n = ft_env_var_copy(l[i]);
		if (!n)
			return (NULL);
		if (!first_n)
		{
			first_n = n;
			last_n = n;
		}
		else
		{
			last_n->next = n;
			last_n = n;
		}
		i++;
	}
	return (first_n);
}

t_envp	*ft_env_var_copy(char *s)
{
	char	*a;
	t_envp	*n;

	n = malloc(sizeof(t_envp));
	if (!n)
		return (NULL);
	a = ft_strchr(s, '=');
	if (!a)
		return (free(n), NULL);
	n->var = ft_strndup(s, a - s);
	if (!n->var)
		return (ft_free_all(2, n->var, n->value), NULL);
	n->value = ft_strdup(a + 1);
	if (!n->value)
		return (free(n), NULL);
	n->next = NULL;
	n->export = 1;
	return (n);
}
