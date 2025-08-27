/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prompt_and_list_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:03:07 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/27 23:06:15 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_env_prompt(void)
{
    char    *p;
    char    *c;

    c = getcwd(NULL, 0);
    if (!c)
    {
        p = malloc(ft_strlen("minishell > ") + 1);
        if (!p)
            return (NULL);
        ft_strcpy(p, "minishell > ");
        return (p);
    }
    p = malloc((sizeof("minishell ") - 1)
               + ft_strlen(c)
               + (sizeof(" > ") - 1)
               + 1);
    if (!p)
        return (free(c), NULL);

    ft_strcpy(p, "minishell ");
    ft_strcpy(p + (sizeof("minishell ") - 1), c);
    ft_strcpy(p + (sizeof("minishell ") - 1) + ft_strlen(c), " > ");

    free(c);
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
