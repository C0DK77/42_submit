/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:25 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 19:31:04 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_special_tokens(t_token **token_list, t_command **current)
{
	if (is_redir((*token_list)->type))
		return (add_redir(token_list, current));
	if ((*token_list)->type == LITERAL || (*token_list)->type == DOLLAR
		|| (*token_list)->type == SPECIAL_VARIABLE)
		return (handle_cmd_or_arg(token_list, current));
	if ((*token_list)->type == PIPE)
		return (handle_pipe(token_list, current));
	return (-1);
}


