/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:43:58 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 10:19:23 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_and_return(t_character *chars, t_token *toks, t_command *cmds,
		int code)
{
	if (cmds)
		cleanup(cmds);
	if (toks)
		free_token_list(toks);
	if (chars)
		free_character_list(chars);
	return (code);
}

static int	one_shot(char *line, t_shell *sh)
{
	t_character	*chars;
	t_token		*toks;
	t_command	*cmds;
	t_all		*all;
	int			code;

	all = get_all(1);
	chars = build_char_list(line);
	if (!chars)
		return (1);
	all->char_list = chars;
	toks = build_token_list(all->char_list);
	if (!toks)
		return (free_and_return(chars, NULL, NULL, 1));
	all->token_list = toks;
	cmds = init_struct_globale(all->token_list);
	if (!cmds)
		return (free_and_return(chars, toks, NULL, 1));
	all->command_list = cmds;
	expander(&cmds, sh);
	code = run_pipeline(all, cmds, sh);
	return (free_and_return(chars, toks, cmds, code));
}

static void	lauch_minishell(t_shell *shell)
{
	char	*line;
	int		code;

	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (check_signals())
			shell->last_exit = 130;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		code = one_shot(line, shell);
		free(line);
		shell->last_exit = code;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	s;

	(void)av;
	if (ac != 1)
		return (1);
	if (!ft_set_env(env, &s))
		return (1);
	lauch_minishell(&s);
	free_env(&s);
	return (s.last_exit);
}
