/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:41:36 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 10:08:23 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_cd(t_command *cmd, t_shell *sh)
{
	char		*a;
	char		old[4096];
	char		new[4096];
	t_element	*t;

	t = cmd->element;
	if (!ft_cmd_cd_check_arg(t))
		return (1);
	a = ft_cmd_cd_arg(cmd->element, sh);
	if (!a)
		return (1);
	if (!getcwd(old, sizeof(old)))
		old[0] = '\0';
	if (chdir(a) != 0)
		return (1);
	if (!getcwd(new, sizeof(new)) || !ft_cmd_set_env(&sh->env, "OLDPWD", old)
		|| !ft_cmd_set_env(&sh->env, "PWD", new))
		return (0);
	return (0);
}

int	ft_cmd_cd_check_arg(t_element *t)
{
	int	i;

	i = 0;
	while (t && t->kind == ARG)
	{
		i++;
		t = t->next;
	}
	if (i > 2)
		return (0);
	return (1);
}

char	*ft_cmd_cd_arg(t_element *lmt, t_shell *sh)
{
	char		*a;
	t_element	*t;

	t = lmt;
	if (t && t->kind == ARG)
		t = t->next;
	while (t && (t->kind != ARG || !t->u_.arg || !t->u_.arg->str
			|| !*t->u_.arg->str))
		t = t->next;
	if (!t)
	{
		a = ft_env_search_value(sh->env, "HOME");
		if (!a)
			return (ft_putstr_fd("minishell: cd: HOME not set\n",
					STDERR_FILENO), NULL);
		return (a);
	}
	return (t->u_.arg->str);
}

int	ft_cmd_set_env(char ***env, char *var, char *c)
{
	if (ft_cmd_cd_replace(*env, var, c))
		return (1);
	return (ft_cmd_cd_append(env, var, c));
}

int	ft_cmd_cd_replace(char **env, char *var, char *value)
{
	size_t	ln;
	int		i;
	char	*nv;

	if (!env)
		return (0);
	ln = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ln) == 0 && env[i][ln] == '=')
		{
			nv = ft_cmd_cd_create(var, value);
			if (!nv)
				return (0);
			free(env[i]);
			env[i] = nv;
			return (1);
		}
		i++;
	}
	return (0);
}
