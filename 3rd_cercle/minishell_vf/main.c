/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:43:58 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 15:13:24 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	s;

	(void)av;
	if (ac != 1)
		return (1);
	if (!ft_set_env(env, &s))
		return (1);
	return (ft_program(&s), ft_free_env(&s), s.last_exit);
}

void	ft_program(t_shell *s)
{
	char	*l;
	int		i;

	ft_signal_init();
	while (1)
	{
		l = readline("minishell$ ");
		if (!l)
		{
			ft_putstr("exit\n");
			break ;
		}
		if (ft_signal_check())
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
	t_all		*a;
	int			i;

	a = get_all(1);
	c = ft_lexer_init(l);
	if (!c)
		return (1);
	a->char_list = c;
	t = ft_token_init(a->char_list);
	if (!t)
		return (ft_free_program(c, NULL, NULL, 1));
	a->token_list = t;
	cmd = init_struct_globale(a->token_list);
	if (!cmd)
		return (ft_free_program(c, t, NULL, 1));
	a->command_list = cmd;
	expander(&cmd, s);
	i = run_pipeline(a, cmd, s);
	return (ft_free_program(c, t, cmd, i));
}

int	ft_free_program(t_character *c, t_token *t, t_command *cmd, int i)
{
	if (cmd)
		cleanup(cmd);
	if (t)
		free_token_list(t);
	if (c)
		free_character_list(c);
	return (i);
}

void	ft_free_env(t_shell *s)
{
	size_t i;

	if (!s || !s->env)
		return ;
	i = 0;
	while (s->env[i] != NULL)
		free(s->env[i++]);
	free(s->env);
	s->env = NULL;
}