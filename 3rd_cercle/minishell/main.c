/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/03 15:12:14 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_envp	*c_envp;
	t_token	*tokens;
	t_token	*tmp;

	(void)argc;
	(void)argv;
	c_envp = ft_init_envp(envp);
	if (!c_envp)
		return (1);
	if (!ft_check_all_var(&c_envp))
		return (0);
	while ((line = readline(ft_prompt())) != NULL)
	{
		if (*line)
			add_history(line);
		printf("LINE => %s\n", line);
		tokens = ft_parse_line(line, c_envp);
		tmp = tokens;
		while (tmp)
		{
			printf("[TOKEN] type=%d  value='%s'\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
	}
	free(c_envp);
	printf("exit\n");
	return (0);
}
