/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/02 18:50:29 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_envp	*c_envp;

	(void)argc;
	(void)argv;
	c_envp = ft_init_env(envp);
	if (!c_envp)
		return (1);
	if (!ft_check_all_var(c_envp))
		return (0);
	while ((line = readline(prompt())) != NULL)
	{
		if (*line)
			add_history(line);
		printf("LINE => %s\n", line);
		ft_parse_line(line);
		free(line);
	}
	free(c_envp);
	printf("exit\n");
	return (0);
}
