/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:24:59 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/27 16:20:06 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_min_env(t_envp *c_envp)
{
	char	b[PATH_MAX];

	if (!getcwd(b, sizeof(b)))
		return ;
	ft_pwd_export_env_set(&c_envp, "_", "/bin/env", 0);
	ft_pwd_export_env_set(&c_envp, "OLDPWD", NULL, 0);
	ft_pwd_export_env_set(&c_envp, "SHLVL", "1", 0);
	ft_pwd_export_env_set(&c_envp, "PWD", b, 0);
}
