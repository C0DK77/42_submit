/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:41:55 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 09:44:29 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_exit(t_command *cmd, t_shell *sh, t_all *a)
{
	size_t			argc;
	char			**argv;
	int				i;
	unsigned char	c;

	argv = ft_cmd_exit_arg(cmd, &argc);
	if (!argv)
		return (1);
	i = 0;
	if (argv[0] && !ft_strncmp(argv[0], "exit", ft_strlen(argv[0]) + 1))
		i = 1;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!argv[i])
		ft_cmd_exit_no_arg(argv, sh, a);
	if (!ft_cmd_exit_isnum(argv[i]))
		ft_cmd_exit_error(argv, i, sh, a);
	c = ft_atoi(argv[i]);
	free(argv);
	ft_free_env(sh);
	ft_free_all(a->ch, a->tk, a->cmd);
	rl_clear_history();
	exit(c);
}

char	**ft_cmd_exit_arg(t_command *cmd, size_t *argc)
{
	t_element	*e;
	char		**argv;
	size_t		i;

	*argc = 0;
	e = cmd->element;
	while (e)
	{
		if (e->kind == ARG)
			(*argc)++;
		e = e->next;
	}
	argv = (char **)ft_calloc(*argc + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	e = cmd->element;
	while (e)
	{
		if (e->kind == ARG)
			argv[i++] = e->u_.arg->str;
		e = e->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	ft_cmd_exit_no_arg(char **s, t_shell *sh, t_all *a)
{
	free(s);
	ft_free_env(sh);
	ft_free_all(a->ch, a->tk, a->cmd);
	rl_clear_history();
	exit(sh->last_exit);
}

int	ft_cmd_exit_isnum(char *s)
{
	char	*p;

	p = s;
	if (!s || !*s)
		return (0);
	if (*p == '+' || *p == '-')
		p++;
	if (!*p)
		return (0);
	while (*p)
	{
		if (*p < '0' || *p > '9')
			return (0);
		p++;
	}
	return (1);
}

void	ft_cmd_exit_error(char **argv, int i, t_shell *sh, t_all *a)
{
	ft_putall_fd(STDERR_FILENO, 3, "minishell: exit: ", argv[i],
		": numeric argument required\n");
	free(argv);
	ft_free_env(sh);
	ft_free_all(a->ch, a->tk, a->cmd);
	rl_clear_history();
	exit(2);
}
