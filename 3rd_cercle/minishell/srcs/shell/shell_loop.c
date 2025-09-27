/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:23:32 by ecid              #+#    #+#             */
/*   Updated: 2025/09/27 17:26:44 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*shell_readline(void)
{
	char	*line;

	line = readline(ft_env_prompt());
	if (!line)
		printf("exit\n");
	else if (*line)
		add_history(line);
	return (line);
}

static t_parsing	*parse_from_line(char *line, t_envp *env)
{
	t_token		*tokens;
	t_parsing	*ast;

	tokens = ft_token(line, env);
	if (!tokens || !ft_token_check(tokens))
	{
		ft_token_free(tokens);
		return (NULL);
	}
	ast = ft_parse_line(tokens);
	ft_token_free(tokens);
	return (ast);
}

int	ft_shell_loop(t_envp **c_envp)
{
	char		*line;
	t_parsing	*parse;

	line = shell_readline();
	if (!line)
		return (0);
	parse = parse_from_line(line, *c_envp);
	free(line);
	if (!parse)
		return (1);
	signal(SIGINT, ft_handler_exec);
	signal(SIGQUIT, ft_handler_exec);
	ft_exec(parse, c_envp);
	setup_signals();
	return (1);
}
