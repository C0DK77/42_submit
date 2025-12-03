/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:40:56 by codk              #+#    #+#             */
/*   Updated: 2025/12/03 12:26:33 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_unset(t_command *cmd, t_shell *s)
{
	size_t	argc;
	char	**argv;
	char	**args;
	int		i;

	argc = ft_count_arg(cmd->element);
	argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		return (1);
	ft_fill_element(cmd->element, argv);
	args = argv;
	if (args[0] && ft_strncmp(args[0], "unset", 5) == 0)
		args++;
	i = ft_cmd_unset_arg(args, s);
	return (free(argv), i);
}

int	ft_cmd_unset_arg(char **args, t_shell *s)
{
	int	status;

	status = 0;
	while (*args)
	{
		if (!ft_cmd_unset_isid(*args))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			if (*args)
				ft_putstr_fd(*args, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			status = 1;
		}
		else
			ft_cmd_unset_remove_env(&s->env, *args);
		args++;
	}
	return (status);
}

int	ft_cmd_unset_isid(char *s)
{
	size_t	i;

	i = 0;
	if (!s || !(ft_isalpha(s[i]) || s[i] == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(ft_isalpha(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_cmd_unset_remove_env(char ***a, char *name)
{
	char	**env;
	size_t	i;
	int		w;
	int		r;

	env = *a;
	if (!env)
		return ;
	i = ft_strlen(name);
	w = 0;
	r = 0;
	while (env[r])
	{
		if (!(ft_strncmp(env[r], name, i) == 0 && env[r][i] == '='))
			env[w++] = env[r];
		else
			free(env[r]);
		r++;
	}
	env[w] = NULL;
}
