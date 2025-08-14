/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/14 16:01:01 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;
t_history	*g_history = NULL;

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
		line = readline(ft_env_prompt());
		if (line && *line)
			ft_history_add(&g_history, line);
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
		p = parse;
		while (p)
		{
			if (p->sep == SEP_NONE && ft_exec_builtin(p->line, &c_envp))
			{
				// printf("[PARENT] Builtin exécuté : %s\n", p->line[0]);
				p = p->next;
			}
			else
			{
				pid = fork();
				if (pid == 0)
				{
					// printf("[CHILD] Je suis le fils pour : %s\n",
					// p->line[0]);
					reset_signals();
					if (ft_exec_redirections_init(p) != 0)
						exit(1);
					if (p->sep != SEP_NONE && ft_exec_builtin(p->line, &c_envp))
					{
						// printf("[CHILD] Builtin exécuté dans pipe : %s\n",
						// p->line[0]);
						exit(g_exit_status);
					}
					// printf("[CHILD] Commande externe : %s\n", p->line[0]);
					ft_exec_cmd(p->line, c_envp);
					exit(1);
				}
				else
				{
					waitpid(pid, &g_exit_status, 0);
					unlink("/tmp/.minishell_heredoc");
				}
				p = p->next;
			}
		}
		ft_token_free(tokens);
		free(line);
	}
	ft_env_free(c_envp);
	return (0);
}
