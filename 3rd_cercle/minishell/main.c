/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/11 13:13:46 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*next;
	char		*t;
	t_envp		*c_envp;
	t_token		*tokens;
	t_parsing	*parse;
	t_parsing	*p;
	pid_t		pid;

	(void)argc;
	(void)argv;
	c_envp = ft_init_envp(envp);
	if (!c_envp)
		return (1);
	if (!ft_check_all_var(&c_envp))
		return (0);
	while (1)
	{
		line = readline(ft_prompt());
		if (!line)
			break ;
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
		if (!line)
			break ;
		if (*line)
			add_history(line);
		// printf("LINE => %s\n", line);
		tokens = ft_parse_line(line, c_envp);
		// ft_print_token(tokens);
		if (!tokens || !check_token_syntax(tokens))
		{
			ft_free_token(tokens);
			free(line);
			continue ;
		}
		parse = ft_parsing_line(tokens);
		// ft_print_parsing(parse);
		p = parse;
		while (p)
		{
			pid = fork();
			if (pid == 0)
			{
				if (setup_redirections(p) != 0)
					exit(1);
				exec_cmd(p->line, c_envp);
				exit(0);
			}
			else
			{
				waitpid(pid, &g_exit_status, 0);
				unlink("/tmp/.minishell_heredoc");
			}
			p = p->next;
		}
		ft_free_token(tokens);
		free(line);
	}
	ft_free_envp(c_envp);
	printf("exit\n");
	return (0);
}
