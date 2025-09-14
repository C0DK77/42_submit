/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/13 21:34:45 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_envp	*c_envp;

	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	c_envp = ft_env_list_init(envp);
	if (!c_envp)
		init_min_env(c_envp);
	if (!ft_env_vars_check(&c_envp))
		return (0);
	setup_signals();
	signal(SIGTSTP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	while (1)
	{
		if (!ft_program(&c_envp))
			break ;
	}
	ft_env_free(c_envp);
	return (0);
}

int	ft_program(t_envp **c_envp)
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

void	init_min_env(t_envp *c_envp)
{
	char	b[PATH_MAX];

	if (!getcwd(b, sizeof(b)))
		return ;
	ft_pwd_export_env_set(&c_envp, "_", "/bin/env", 0);
	ft_pwd_export_env_set(&c_envp, "OLDPWD", NULL, 0);
	ft_pwd_export_env_set(&c_envp, "SHLVL", "1", 0);
	ft_pwd_export_env_set(&c_envp, "PWD", b, 0);
}
