/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/02 16:16:44 by corentindes      ###   ########.fr       */
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
		parse(line);
		free(line);
	}
	free(c_envp);
	printf("exit\n");
	return (0);
}

void	parse(char *line)
{
	int i;
	t_token *split_line;

	i = 0;
	split_line = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		else if (ft_isoperator(line[i]))
			parse_operator(line, i);
		else if (ft_issinglequote(line[i]))
			ft_parse_word_issinglequote(line, i);
		else if (ft_isdoublequote(line[i]))
			ft_parse_word_isdoublequote(line, i);
		else if (!ft_isspace(line[i]))
			ft_parse_word_withoutquotes(line, i);
	}
}