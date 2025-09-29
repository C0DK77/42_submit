/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 18:05:58 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_envp	*env;

	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	if (!envp || !*envp)
		env = NULL;
	else
		env = ft_env_list_init(envp);
	if (!ft_env_vars_check(&env))
		return (1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		if (!ft_program(env))
			break ;
	ft_env_free(env);
	return (0);
}

int	ft_program(t_envp *env)
{
	char		*s;
	t_token		*tokens;
	t_parsing	*parse;

	s = readline(ft_env_prompt());
	if (!s)
		return (printf("exit\n"), 0);
	if (*s)
		add_history(s);
	s = ft_program_check_unclosed_quote(s);
	if (!s)
		return (1);
	tokens = ft_token(env, s);
	if (!tokens)
		return (free(s), 1);
	if (!ft_token_check(tokens))
		return (ft_token_free(tokens), free(s), 1);
	parse = ft_parse_line(env, tokens);
	if (!parse)
		return (ft_token_free(tokens), free(s), 1);
	ft_exec(parse, env);
	return (ft_token_free(tokens), free(s), 1);
}

char	*ft_program_check_unclosed_quote(char *s)
{
	char	*n;
	char	*t;

	while (ft_has_unclosed_quote(s))
	{
		n = readline("> ");
		if (!n)
		{
			ft_putstr_fd("minishell: syntax error: unexpected end of file\n",
				2);
			g_exit_status = 2;
			free(s);
			return (NULL);
		}
		t = ft_strjoin(s, "\n");
		free(s);
		s = ft_strjoin(t, n);
		ft_free_all(2, t, n);
	}
	return (s);
}
