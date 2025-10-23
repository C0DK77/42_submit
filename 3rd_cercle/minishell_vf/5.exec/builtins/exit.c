/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:41:55 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 07:01:48 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_no_arg(char **argv, t_shell *sh, t_all *all)
{
	free(argv);
	free_env(sh);
	cleanall(all->char_list, all->token_list, all->command_list);
	rl_clear_history();
	exit(sh->last_exit);
}

static void	exit_numeric_error(char **argv, int idx, t_shell *sh, t_all *all)
{
	ft_putall_fd(STDERR_FILENO, 3, "minishell: exit: ", argv[idx],
		": numeric argument required\n");
	free(argv);
	free_env(sh);
	cleanall(all->char_list, all->token_list, all->command_list);
	rl_clear_history();
	exit(2);
}

static char	**collect_args(t_command *cmd, size_t *argc)
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

int	builtin_exit(t_command *cmd, t_shell *s, t_all *a)
{
	size_t			argc;
	char			**argv;
	int				idx;
	unsigned char	code;

	argv = collect_args(cmd, &argc);
	if (!argv)
		return (1);
	idx = 0;
	if (argv[0] && !ft_strncmp(argv[0], "exit", ft_strlen(argv[0]) + 1))
		idx = 1;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!argv[idx])
		exit_no_arg(argv, s, a);
	if (!is_numeric_word(argv[idx]))
		exit_numeric_error(argv, idx, s, a);
	code = ft_atoi(argv[idx]);
	free(argv);
	free_env(s);
	cleanall(a->char_list, a->token_list, a->command_list);
	rl_clear_history();
	exit(code);
}
