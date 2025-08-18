/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/18 18:13:19 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*next;
	char		*prompt;
	char		*t;
	t_envp		*c_envp;
	t_token		*tokens;
	t_parsing	*parse;

	// char		*pwd;
	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	c_envp = ft_env_init(envp);
	if (!c_envp)
		return (1);
	if (!ft_vars_check(&c_envp))
		return (0);
	setup_signals();
	while (1)
	{
		prompt = ft_env_prompt();
		line = readline(prompt);
		free(prompt);//changement pour liberer la memoire sinon fuite 
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		while (ft_has_unclosed_quote(line))
		{
			next = readline("> ");
			if (!next)
				break ;
			t = ft_strjoin(line, "\n");
			free(line);
			line = ft_strjoin(t, next);
			free(t);
			free(next);
		}
		if (*line)
			add_history(line);
		// printf("LINE => %s\n", line);
		tokens = ft_token(line, c_envp);
		// ft_print_token(tokens);
		if (!tokens || !ft_token_check(tokens))
		{
			ft_token_free(tokens);
			free(line);
			continue ;
		}
		parse = ft_parse_line(tokens);
		// ft_print_parsing(parse);
		ft_exec(parse, c_envp);
		unlink("/tmp/.minishell_heredoc");
		ft_token_free(tokens);
		free(line);
	}
	ft_env_free(c_envp);
	return (0);
}
