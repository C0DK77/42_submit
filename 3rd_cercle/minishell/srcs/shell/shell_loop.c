/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:23:32 by ecid              #+#    #+#             */
/*   Updated: 2025/09/27 16:30:24 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_shell_loop(t_envp **c_envp)
{
	char		*line;
	t_token		*tokens;
	t_parsing	*parse;

	line = readline(ft_env_prompt());
	if (!line)
	{
		printf("exit\n");
		return (0);
	}
	if (*line)
		add_history(line);
	tokens = ft_token(line, *c_envp);
	if (!tokens || !ft_token_check(tokens))
	{
		ft_token_free(tokens);
		free(line);
		return (1);
	}
	parse = ft_parse_line(tokens);
	ft_token_free(tokens);
	free(line);
	if (!parse)
		return (1);
	signal(SIGINT, ft_handler_exec);
	signal(SIGQUIT, ft_handler_exec);
	ft_exec(parse, c_envp);
	setup_signals();
	return (1);
}

