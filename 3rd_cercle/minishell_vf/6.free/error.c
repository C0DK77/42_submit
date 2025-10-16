/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:42:59 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 15:42:27 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *msg)
{
	ft_putall_fd(2, 3, "minishell: ", msg, "\n");
}

void	print_syntax_error(char *token)
{
	if (token)
		ft_putall_fd(2, 3, "minishell: syntax error near unexpected token `",
			token, "'\n");
	else
		ft_putall_fd(2, 3, "minishell: syntax error near unexpected token `",
			"newline", "'\n");
}

int	exit_too_many_args(void)
{
	return (ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO),
		1);
}
