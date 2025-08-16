/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 16:11:42 by corentindes      ###   ########.fr       */
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
	//	permet d'avoir les sorties printf directement dans la sortie sans bufferisation
	setbuf(stdout, NULL);
	// c_envp permet d'avoir une structure des variables d'environnement pour plus de simplicite
	c_envp = ft_env_list_init(envp);
	if (!c_envp)
		return (1);
	// check si des variables sont absentes de la list c_envp
	if (!ft_env_vars_check(&c_envp))
		return (0);
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		if (!program(c_envp))
			break ;
	ft_env_free(c_envp);
	return (0);
}

int	program(t_envp *c_envp)
{
	char *line;
	char *next;
	char *t;
	t_token *tokens;
	t_parsing *parse;
	t_parsing *p;
	pid_t pid;

	line = readline(ft_env_prompt());
	if (line && *line)
		ft_history_add(&g_history, line);
	if (!line)
		return (printf("exit\n"), 0);
	while (ft_has_unclosed_quote(line))
	{
		next = readline("> ");
		if (!next)
			break ;
		t = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(t, next);
		free(t);
		free(next);
	}
	if (*line)
		add_history(line);
	// printf("LINE => %s\n", line);
	tokens = ft_token(line, c_envp);
	// ft_print_token(tokens);
	if (!tokens || !ft_token_check(tokens))
		return (ft_token_free(tokens), free(line), 1);
	parse = ft_parse_line(tokens);
	// ft_print_parsing(parse);
	p = parse;
	while (p)
	{
		if (p->sep == SEP_NONE && ft_exec_builtin(p->line, &c_envp))
		{
			// printf("[PARENT] Builtin exécuté : %s\n", p->line[0]);
			p = p->next;
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				// printf("[CHILD] Je suis le fils pour : %s\n",
				// p->line[0]);
				if (ft_exec_redirections_init(p) != 0)
					exit(1);
				if (p->sep != SEP_NONE && ft_exec_builtin(p->line, &c_envp))
				{
					// printf("[CHILD] Builtin exécuté dans pipe : %s\n",
					// p->line[0]);
					exit(g_exit_status);
				}
				// printf("[CHILD] Commande externe : %s\n", p->line[0]);
				ft_exec_cmd(p->line, c_envp);
				exit(1);
			}
			else
			{
				waitpid(pid, &g_exit_status, 0);
				unlink("/tmp/.minishell_heredoc");
			}
			p = p->next;
		}
	}
	return (ft_token_free(tokens), free(line), 1);
}

