/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:42:02 by codk              #+#    #+#             */
/*   Updated: 2025/10/25 07:53:15 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_export(t_command *cmd, t_shell *sh)
{
	char	**argv;
	int		i;
	int		status;
	size_t	argc;

	argc = ft_count_arg(cmd->element);
	argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	argv = ft_fill_argv(cmd->element, argv);
	if (!argv)
		return (1);
	i = 0;
	if (argv[0] && ft_strncmp(argv[0], "export", 6) == 0)
		i = 1;
	if (!argv[i])
	{
		status = ft_cmd_export_print(sh);
		return (free(argv), status);
	}
	status = ft_cmd_export_arg(argv, i, sh);
	return (free(argv), status);
}

int	ft_cmd_export_print(t_shell *sh)
{
	int		i;
	char	*eq;
	size_t	ln;

	i = 0;
	while (sh->env && sh->env[i])
	{
		eq = ft_strchr(sh->env[i], '=');
		if (!eq)
			ft_putall_fd(STDOUT_FILENO, 3, "declare -x ", sh->env[i], "\n");
		ln = (size_t)(eq - sh->env[i]);
		ft_putall_fd(STDOUT_FILENO, 5, "declare -x ", sh->env[i], "=\"", eq + 1,
			"\"\n");
		i++;
	}
	return (0);
}

int	ft_cmd_export_arg(char **argv, int i, t_shell *sh)
{
	int	status;

	status = 0;
	while (argv[i])
	{
		if (!ft_cmd_export_arg_create(argv[i], sh))
			status = 1;
		i++;
	}
	return (status);
}

int	ft_cmd_export_arg_create(char *a, t_shell *s)
{
	char	*eq;
	char	*name;

	if (!ft_cmd_export_isval(a))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		if (a)
			ft_putstr_fd(a, STDERR_FILENO);
		return (ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO), 0);
	}
	eq = ft_strchr(a, '=');
	if (eq)
	{
		name = ft_strndup(a, (size_t)(eq - a));
		if (!name)
			return (0);
		if (!ft_cmd_export_set_env(&s->env, name, eq + 1))
			return (free(name), 0);
		return (free(name), 1);
	}
	if (!ft_cmd_export_set_env(&s->env, a, ""))
		return (0);
	return (1);
}

int	ft_cmd_export_isval(char *s)
{
	size_t	i;

	i = 0;
	if (!s || !is_var_start(s[i]))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!is_var_continue(s[i]))
			return (0);
		i++;
	}
	return (1);
}
