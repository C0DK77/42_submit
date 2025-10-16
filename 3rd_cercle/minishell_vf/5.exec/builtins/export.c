/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:42:02 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 00:21:47 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export_line(char *a)
{
	char	*eq;
	size_t	ln;

	eq = ft_strchr(a, '=');
	if (!eq)
		return (ft_putall_fd(STDOUT_FILENO, 3, "declare -x ", a, "\n"));
	ln = (size_t)(eq - a);
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(a, STDOUT_FILENO);
	ft_putall_fd(STDOUT_FILENO, 3, "=\"", eq + 1, "\"\n");
}

void	print_export_error(const char *s)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	handle_export_arg(char *a, t_shell *s)
{
	const char	*eq;
	char		*name;

	if (!is_valid_ident_export(a))
		return (print_export_error(a), 0);
	eq = ft_strchr(a, '=');
	if (eq)
	{
		name = dup_n(a, (size_t)(eq - a));
		if (!name)
			return (0);
		if (!setenv_in_vec(&s->env, name, eq + 1))
			return (free(name), 0);
		return (free(name), 1);
	}
	if (!setenv_in_vec(&s->env, a, ""))
		return (0);
	return (1);
}

int	builtin_export(t_command *cmd, t_shell *sh)
{
	char	**argv;
	int		idx;
	int		status;

	argv = build_export_argv(cmd->element);
	if (!argv)
		return (1);
	idx = 0;
	if (argv[0] && ft_strncmp(argv[0], "export", 6) == 0)
		idx = 1;
	if (!argv[idx])
	{
		status = print_all_exports(sh);
		return (free(argv), status);
	}
	status = process_export_args(argv, idx, sh);
	return (free(argv), status);
}
