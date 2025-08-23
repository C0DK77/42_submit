/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/23 08:27:25 by corentindes      ###   ########.fr       */
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
	t_token		*tokens;
	t_parsing	*parse;

	line = readline(ft_env_prompt());
	if (!line)
		return (printf("exit\n"), 0);
	if (*line)
		add_history(line);
	line = ft_program_check_has_unclosed_quote(line);
	tokens = ft_token(line, c_envp);
	if (!tokens || !ft_token_check(tokens))
		return (ft_token_free(tokens), free(line), 1);
	parse = ft_parse_line(tokens);
	ft_program_parse(parse, c_envp);
	return (ft_token_free(tokens), free(line), 1);
}

char	*ft_program_check_has_unclosed_quote(char *line)
{
	char	*n;
	char	*t;

	while (ft_has_unclosed_quote(line))
	{
		n = readline("> ");
		if (!n)
			break ;
		t = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(t, n);
		ft_free_all(2, t, n);
	}
	return (line);
}

void	ft_program_parse(t_parsing *parse, t_envp *c_envp)
{
	pid_t	pid;
	int		status;

	while (parse)
	{
		if (parse->sep == SEP_NONE && ft_exec_builtin(parse->line, &c_envp))
			parse = parse->next;
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (ft_exec_redirections_init(parse) != 0)
					exit(1);
				if (parse->sep != SEP_NONE && ft_exec_builtin(parse->line,
						&c_envp))
					exit(g_exit_status);
				ft_exec_cmd(parse->line, c_envp);
				exit(1);
			}
			else
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					g_exit_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					g_exit_status = 128 + WTERMSIG(status);
				unlink(HEREDOC_FILE);
			}
			parse = parse->next;
		}
	}
}
