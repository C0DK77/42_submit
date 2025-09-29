/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prompt_and_list_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:31:50 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 09:42:31 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_env_prompt(void)
{
	char	*prompt;
	char	*c;

	c = getcwd(NULL, 0);
	if (!c)
	{
		perror("getcwd");
		prompt = malloc(ft_strlen("minishell > ") + 1);
		if (!prompt)
			return (NULL);
		ft_strcpy(prompt, "minishell > ");
		return (prompt);
	}
	prompt = malloc(ft_strlen(c) + 4);
	if (!prompt)
		return (free(c), NULL);
	ft_strcpy(prompt, c);
	prompt[ft_strlen(c)] = ' ';
	prompt[ft_strlen(c) + 1] = '>';
	prompt[ft_strlen(c) + 2] = ' ';
	prompt[ft_strlen(c) + 3] = '\0';
	return (free(c), prompt);
}

t_envp	*ft_env_list_init(char **l)
{
	t_envp	*fst_n;
	t_envp	*lst_n;
	t_envp	*n;

	fst_n = NULL;
	lst_n = NULL;
	while (*l)
	{
		n = ft_env_var_copy(*l);
		if (!n)
			return (NULL);
		if (!fst_n)
			fst_n = n;
		else
			lst_n->next = n;
		lst_n = n;
		l++;
	}
	return (fst_n);
}

t_envp	*ft_env_var_copy(char *s)
{
	char	*a;
	t_envp	*env;

	env = malloc(sizeof(t_envp));
	if (!env)
		return (NULL);
	a = ft_strchr(s, '=');
	if (!a)
		return (free(env), NULL);
	env->var = ft_strndup(s, a - s);
	if (!env->var)
		return (ft_free_all(2, env->var, env->value), NULL);
	env->value = ft_strdup(a + 1);
	if (!env->value)
		return (free(env), NULL);
	env->next = NULL;
	env->export = 1;
	return (env);
}
