/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_norme.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:40:31 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 04:40:33 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	apply_redirs(const t_ios *ios)
{
	if (ios->in_fd >= 0)
	{
		if (dup2(ios->in_fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (0);
		}
	}
	if (ios->out_fd >= 0)
	{
		if (dup2(ios->out_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			return (0);
		}
	}
	return (1);
}

void	close_redirs(t_ios *ios)
{
	if (ios->in_fd >= 0)
	{
		close(ios->in_fd);
		ios->in_fd = -1;
	}
	if (ios->out_fd >= 0)
	{
		close(ios->out_fd);
		ios->out_fd = -1;
	}
}
