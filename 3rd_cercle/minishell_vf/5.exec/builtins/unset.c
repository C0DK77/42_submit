/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:40:56 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 00:25:20 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_unset_error(char *a)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	if (a)
		ft_putstr_fd(a, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	process_unset_args(char **args, t_shell *s)
{
	int	status;

	status = 0;
	while (*args)
	{
		if (!is_valid_ident(*args))
		{
			print_unset_error(*args);
			status = 1;
		}
		else
			remove_env_var(&s->env, *args);
		args++;
	}
	return (status);
}

int	builtin_unset(t_command *cmd, t_shell *s)
{
	size_t	argc;
	char	**argv;
	char	**args;
	int		status;

	argc = count_args(cmd->element);
	argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		return (1);
	fill_argv(cmd->element, argv);
	args = argv;
	if (args[0] && ft_strncmp(args[0], "unset", 5) == 0)
		args++;
	status = process_unset_args(args, s);
	return (free(argv), status);
}
