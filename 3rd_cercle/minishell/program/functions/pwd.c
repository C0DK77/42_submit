/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:20:27 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/22 19:25:03 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_pwd(char **s, t_envp *l)
{
	char	**n;
	int		o;

	n = ft_pwd_check_options(s + 1, &o);
	if (!n)
		return (1);
	if (ft_pwd_options(ft_env_search_value(l, "PWD"), o))
		return (1);
	g_exit_status = 0;
	return (0);
}

char	**ft_pwd_check_options(char **s, int *o)
{
	*o = 0;
	if (!s || !*s)
		return (s);
	while (*s)
	{
		if (!ft_strcmp(*s, "--"))
			return (s + 1);
		if (!ft_strcmp(*s, "-") || (*s)[0] != '-')
			return (s);
		if ((*s)[1] == '-' && (*s)[2] != '\0')
		{
			ft_pwd_error(2, 0);
			return (NULL);
		}
		if (!ft_pwd_put_options(s, o))
			return (NULL);
		s++;
	}
	return (s);
}

int	ft_pwd_options(char *pwd, int o)
{
	char	b[PATH_MAX];

	if (o)
	{
		if (!getcwd(b, sizeof(b)))
			return (ft_pwd_error(0, 0));
		printf("%s\n", b);
	}
	else
	{
		if (pwd && *pwd)
			printf("%s\n", pwd);
		else if (getcwd(b, sizeof(b)))
			printf("%s\n", b);
		else
			return (ft_pwd_error(0, 0));
	}
	return (0);
}

char	**ft_pwd_put_options(char **s, int *p)
{
	int	i;

	i = 1;
	while ((*s)[i])
	{
		if ((*s)[i] == 'L')
			*p = 0;
		else if ((*s)[i] == 'P')
			*p = 1;
		else if ((*s)[i] == '-')
		{
			ft_pwd_error(2, 0);
			return (NULL);
		}
		else
		{
			ft_pwd_error(1, (unsigned char)(*s)[i]);
			return (NULL);
		}
		i++;
	}
	return (s);
}

int	ft_pwd_error(int i, int c)
{
	if (i == 0)
	{
		perror("minishell: pwd");
		g_exit_status = 1;
		return (1);
	}
	else if (i == 1)
	{
		g_exit_status = 2;
		return (ft_putstr_fd("minishell: pwd: -", 2), ft_putchar_fd(c, 2),
			ft_putstr_fd(": invalid option\npwd: usage: pwd [-LP]\n", 2), 0);
	}
	else if (i == 2)
	{
		g_exit_status = 2;
		return (ft_putstr_fd("minishell: pwd: --: invalid option\n\npwd: usage: pwd [-LP]\n",
				2), 0);
	}
	return (1);
}
