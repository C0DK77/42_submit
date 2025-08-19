/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/19 10:21:23 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int			g_exit_status = 0;
t_history	*g_history = NULL;

int	main(int argc, char **argv, char **envp)
{
	t_envp	*c_envp;

	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	c_envp = ft_env_list_init(envp);
	if (!c_envp)
		return (1);
	if (!ft_env_vars_check(&c_envp))
		return (0);
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		if (!ft_program(c_envp))
			break ;
	ft_env_free(c_envp);
	return (0);
}

int	ft_program(t_envp *c_envp)
{
	char		*line;
	char		*next;
	char		*t;
	t_token		*tokens;
	t_parsing	*parse;
	t_parsing	*p;
	pid_t		pid;

	line = readline(ft_env_prompt());
	if (line && *line)
		ft_history_add(&g_history, line);
	if (!line)
		return (printf("exit\n"), 0);
	while (ft_has_unclosed_quote(line))
	{
		next = readline("> ");
		if (!next)
			break ;
		t = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(t, next);
		ft_free_all(2, t, next);
	}
	if (*line)
		add_history(line);
	tokens = ft_token(line, c_envp);
	if (!tokens || !ft_token_check(tokens))
		return (ft_token_free(tokens), free(line), 1);
	parse = ft_parse_line(tokens);
	p = parse;
	while (p)
	{
		if (p->sep == SEP_NONE && ft_exec_builtin(p->line, &c_envp))
			p = p->next;
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (ft_exec_redirections_init(p) != 0)
					exit(1);
				if (p->sep != SEP_NONE && ft_exec_builtin(p->line, &c_envp))
					exit(g_exit_status);
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
	return (ft_token_free(tokens), free(line), 1);
}
