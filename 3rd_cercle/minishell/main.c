/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/26 17:36:14 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
		return (1);
	if (!ft_env_vars_check(&c_envp))
		return (0);
	signal(SIGINT, SIG_IGN);
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
	line = ft_program_check_unclosed_quote(line);
	if (!line)
		return (1);
	tokens = ft_token(line, c_envp);
	if (!tokens || !ft_token_check(tokens))
		return (ft_token_free(tokens), free(line), 1);
	parse = ft_parse_line(tokens);
	ft_exec(parse, c_envp);
	return (ft_token_free(tokens), free(line), 1);
}

char	*ft_program_check_unclosed_quote(char *line)
{
	char	*n;
	char	*t;

	while (ft_has_unclosed_quote(line))
	{
		n = readline("> ");
		if (!n)
		{
			ft_putstr_fd("minishell: syntax error: unexpected end of file\n",
				2);
			g_exit_status = 2;
			free(line);
			return (NULL);
		}
		t = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(t, n);
		ft_free_all(2, t, n);
	}
	return (line);
}
