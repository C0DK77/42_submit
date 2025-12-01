/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:41:49 by codk              #+#    #+#             */
/*   Updated: 2025/11/28 13:55:45 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_env(t_command *cmd, t_shell *s)
{
	size_t	i;
	char	**a;
	int		j;

	i = ft_count_arg(cmd->element);
	a = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!a)
		return (1);
	ft_fill_element(cmd->element, a);
	j = 0;
	if (a[0] && ft_strncmp(a[0], "env", ft_strlen(a[0])) == 0)
		j = 1;
	if (a[j])
		return (ft_putstr_fd("minishell: env: too many arguments\n",
				STDERR_FILENO), free(a), 1);
	return (ft_cmd_env_print(s->env), free(a), 0);
}

void	ft_cmd_env_print(char **e)
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
