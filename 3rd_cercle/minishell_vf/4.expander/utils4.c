/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:35:37 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 04:35:38 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_element	*remove_empty_var_arg(t_command *cmd, t_element *e)
{
	t_element	*next;

	next = e->next;
	cmd->element = next;
	free(e->u_.arg->str);
	free(e->u_.arg);
	free(e);
	return (next);
}
