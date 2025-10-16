/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:41:43 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 00:03:44 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_echo_n(char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

void	print_args(t_element *e)
{
	int	i;

	i = 1;
	while (e)
	{
		if (e->kind == ARG && e->u_.arg && e->u_.arg->str)
		{
			if (!i)
				ft_putchar_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(e->u_.arg->str, STDOUT_FILENO);
			i = 0;
		}
		e = e->next;
	}
}

int	builtin_echo(t_command *cmd, t_shell *s)
{
	int			i;
	t_element	*e;

	(void)s;
	i = 0;
	e = cmd->element;
	if (e && e->kind == ARG)
		e = e->next;
	while (e && e->kind == ARG && e->u_.arg && is_echo_n(e->u_.arg->str))
	{
		i = 1;
		e = e->next;
	}
	print_args(e);
	if (!i)
		ft_putchar_fd("\n", STDOUT_FILENO);
	return (0);
}
