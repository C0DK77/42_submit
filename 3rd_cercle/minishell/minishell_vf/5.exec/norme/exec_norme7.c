/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norme7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:40:06 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 04:40:08 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_on_fail(int *prev_rd, t_pipeinfo *pi)
{
	if (*prev_rd >= 0)
		close(*prev_rd);
	if (pi->need_pipe)
	{
		close(pi->out_wr);
		close(pi->pfd[0]);
	}
}

void	advance_pipe_state(int *prev_rd, t_pipeinfo *pi)
{
	if (*prev_rd >= 0)
		close(*prev_rd);
	if (pi->need_pipe)
	{
		close(pi->out_wr);
		*prev_rd = pi->pfd[0];
	}
	else
		*prev_rd = -1;
}
