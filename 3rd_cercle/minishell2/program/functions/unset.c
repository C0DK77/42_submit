/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:43:17 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/28 23:47:15 by elisacid         ###   ########.fr       */
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

