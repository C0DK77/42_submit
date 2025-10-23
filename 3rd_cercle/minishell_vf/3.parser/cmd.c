/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:25 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 06:37:24 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser_special_tokens(t_token **tk, t_command **cmd)
{
	if ((*tk)->type == HEREDOC || (*tk)->type == APPEND
		|| (*tk)->type == REDIR_IN || (*tk)->type == REDIR_OUT)
		return (ft_parser_add_redir(tk, cmd));
	if ((*tk)->type == LITERAL || (*tk)->type == DOLLAR
		|| (*tk)->type == SPECIAL_VARIABLE)
		return (ft_parser_handle_cmd_or_arg(tk, cmd));
	if ((*tk)->type == PIPE)
		return (ft_parser_handle_pipe(tk, cmd));
	return (-1);
}
