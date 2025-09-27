/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/27 16:31:03 by ecid             ###   ########.fr       */
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
		if (!ft_shell_loop(&c_envp))
			break ;
	}
	ft_env_free(c_envp);
	return (0);
}
