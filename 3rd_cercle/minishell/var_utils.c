/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:03:07 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/09 15:20:57 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_prompt(void)
{
	char	*prompt;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		prompt = malloc(ft_strlen("minishell > ") + 1);
		if (!prompt)
			return (NULL);
		ft_strcpy(prompt, "minishell > ");
		return (prompt);
	}
	prompt = malloc(ft_strlen(cwd) + 4);
	if (!prompt)
	{
		free(cwd);
		return (NULL);
	}
	ft_strcpy(prompt, cwd);
	prompt[ft_strlen(cwd)] = ' ';
	prompt[ft_strlen(cwd) + 1] = '>';
	prompt[ft_strlen(cwd) + 2] = ' ';
	prompt[ft_strlen(cwd) + 3] = '\0';
	return (prompt);
}

t_envp	*ft_create_envp(char *str)
{
	char	*a;
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	a = ft_strchr(str, '=');
	if (!a)
	{
		free(node);
		return (NULL);
	}
	node->var = strndup(str, a - str);
	node->value = ft_strdup(a + 1);
	node->next = NULL;
	if (!node->var || !node->value)
	{
		free(node->var);
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

t_envp	*ft_init_envp(char **envp)
{
	t_envp	*head;
	t_envp	*tail;
	t_envp	*new_node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = ft_create_envp(envp[i]);
		if (!new_node)
			return (NULL);
		if (!head)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		i++;
	}
	return (head);
}

t_envp	*ft_search_var(t_envp *lst, char *var)
{
	while (lst)
	{
		if (strcmp(lst->var, var) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_free_envp(t_envp *lst)
{
	t_envp	*t;

	while (lst)
	{
		t = lst->next;
		free(lst->var);
		free(lst->value);
		free(lst);
		lst = t;
	}
}

char	*ft_search_value(t_envp *lst, char *var)
{
	while (lst)
	{
		if (strcmp(lst->var, var) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}
