/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:43:58 by codk              #+#    #+#             */
/*   Updated: 2025/10/20 04:02:52 by corentindes      ###   ########.fr       */
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
	t_command	*l;
	t_all		*a;
	int			i;

	a = ft_init_all(1);
	c = ft_lexer_init(l);
	if (!c)
		return (1);
	a->ch = c;
	t = ft_token_init(a->ch);
	if (!t)
		return (ft_free_program(c, NULL, NULL, 1));
	a->tk = t;
	l = ft_parser_init(a->tk);
	if (!l)
		return (ft_free_program(c, t, NULL, 1));
	a->cmd = l;
	expander(&l, s);
	i = run_pipeline(a, l, s);
	return (ft_free_program(c, t, l, i));
}
