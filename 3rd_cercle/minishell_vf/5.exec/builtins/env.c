/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:41:49 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 00:04:44 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exec_print_env(char **e)
{
	size_t	i;

	i = 0;
	while (e && e[i])
	{
		if (ft_strchr(e[i], '='))
			ft_putall_fd(STDOUT_FILENO, 2, e[i], "\n");
		i++;
	}
}

int	builtin_env(t_command *cmd, t_shell *s)
{
	size_t	i;
	char	**a;
	int		j;

	i = count_args(cmd->element);
	a = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!a)
		return (1);
	fill_a(cmd->element, a);
	j = 0;
	if (a[0] && ft_strncmp(a[0], "env", ft_strlen(a[0])) == 0)
		j = 1;
	if (a[j])
		return (ft_putstr_fd("minishell: env: too many arguments\n",
				STDERR_FILENO), free(a), 1);
	return (print_env(s->env), free(a), 0);
}
