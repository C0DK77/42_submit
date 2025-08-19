/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:08:40 by ecid              #+#    #+#             */
/*   Updated: 2025/08/17 17:09:00 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pwd_opts(char **s, int *p)
{
	int	i;
	int	j;

	i = 1;
	*p = 0;
	while (s[i])
	{
		if (s[i][0] != '-' || s[i][1] == '\0')
			break ;
		if (!ft_strcmp(s[i], "--"))
		{
			i++;
			break ;
		}
		j = 1;
		while (s[i][j])
		{
			if (s[i][j] == 'P')
				*p = 1;
			else if (s[i][j] == 'L')
				*p = 0;
			else
			{
				fprintf(stderr, "minishell: pwd: -%c: invalid option\n",
					s[i][j]);
				fprintf(stderr, "usage: pwd [-L | -P]\n");
				g_exit_status = 2;
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_pwd(char **s, t_envp *l)
{
	int		i;
	int		n;
	char	b[PATH_MAX];
	char	*pwd;

	pwd = ft_env_search_value(l, "PWD");
	n = parse_pwd_opts(s, &i);
	if (n < 0)
		return (1);
	if (i)
	{
		if (!getcwd(b, sizeof(b)))
		{
			perror("minishell: pwd");
			g_exit_status = 1;
			return (1);
		}
		printf("%s\n", b);
	}
	else
	{
		if (pwd && *pwd)
			printf("%s\n", pwd);
		else
		{
			if (!getcwd(b, sizeof(b)))
			{
				perror("minishell: pwd");
				g_exit_status = 1;
				return (1);
			}
			printf("%s\n", b);
		}
	}
	g_exit_status = 0;
	return (0);
}

void	update_pwd_vars(t_envp *l, char *s)
{
	char	c[PATH_MAX];

	if (s)
		ft_env_set(&l, "OLDPWD", s, 1);
	if (getcwd(c, sizeof(c)))
		ft_env_set(&l, "PWD", c, 1);
}
