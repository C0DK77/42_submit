/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:25:51 by ecid              #+#    #+#             */
/*   Updated: 2025/09/13 15:55:11 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **s, t_envp **l)
{
	int		ret;
	char	**cur;

	ret = 0;
	cur = s + 1;
	while (*cur)
	{
		if ((*cur)[0] == '-' && (*cur)[1] != '\0')
		{
			ft_unset_error(0, *cur);
			cur++;
			continue ;
		}
		if (!ft_unset_check_identifier(cur))
			ret = 1;
		else
			ft_unset_change(cur, l);
		cur++;
	}
	g_exit_status = (ret != 0);
	return (g_exit_status);
}
