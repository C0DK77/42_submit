/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:12:03 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/22 14:35:56 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	update_pwd_vars(t_envp *l, char *s)
{
	char	c[PATH_MAX];

	if (s)
		ft_env_set(&l, "OLDPWD", s, 1);
	if (getcwd(c, sizeof(c)))
		ft_env_set(&l, "PWD", c, 1);
}
