/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:11:25 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/01 11:33:00 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
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