/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 22:32:18 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

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

int	ft_program(t_envp **c_envp)
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


int	main(int argc, char **argv, char **envp)
{
	t_envp	*c_envp;

	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	printf("🛠️  [main] Début du programme\n");
	c_envp = ft_env_list_init(envp);
	if (!c_envp)
		init_min_env(c_envp);
	if (!ft_env_vars_check(&c_envp))
		return (0);//on retourne pas pareil la!!   
	setup_signals();
	signal(SIGTSTP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	while (1)
		if (!ft_program(&c_envp))
			break ;
	ft_env_free(c_envp);
	return (0);
}

