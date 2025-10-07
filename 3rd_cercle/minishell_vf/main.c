/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:43:58 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 16:20:36 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_and_return(t_character *c, t_token *t, t_command *cmd, int i)
{
	if (cmd)
		cleanup(cmd);
	if (t)
		free_token_list(t);
	if (c)
		free_character_list(c);
	return (i);
}

int	main(int ac, char **av, char **env)
{
	t_shell	s;

	(void)av;
	if (ac != 1)
		return (1);
	if (!ft_set_env(env, &s))
		return (1);
	ft_program(&s);
	free_env(&s);
	return (s.last_exit);
}

void	ft_program(t_shell *s)
{
	char	*l;
	int		i;

	setup_signals();
	while (1)
	{
		l = readline("minishell$ ");
		if (!l)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (check_signals())
			s->last_exit = 130;
		if (*l == '\0')
		{
			free(l);
			continue ;
		}
		add_history(l);
		i = ft_program_bis(l, s);
		free(l);
		s->last_exit = i;
	}
}

int	ft_program_bis(char *l, t_shell *s)
{
	t_character	*c;
	t_token		*t;
	t_command	*cmd;
	t_all		*all;
	int			i;

	all = get_all(1);
	c = ft_lexer_init_list(l);
	if (!c)
		return (1);
	all->char_list = c;
	t = build_token_list(all->char_list);
	if (!t)
		return (free_and_return(c, NULL, NULL, 1));
	all->token_list = t;
	cmd = init_struct_globale(all->token_list);
	if (!cmd)
		return (free_and_return(c, t, NULL, 1));
	all->command_list = cmd;
	expander(&cmd, s);
	i = run_pipeline(all, cmd, s);
	return (free_and_return(c, t, cmd, i));
}
