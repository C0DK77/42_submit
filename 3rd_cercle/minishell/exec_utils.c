/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:18 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/09 15:25:09 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	setup_redirections(t_parsing *cmd)
{
	int	fd;

	if (cmd->infile)
	{
		if (cmd->heredoc)
		{
			fd = open(cmd->infile, O_RDONLY);
			if (fd < 0)
			{
				perror("heredoc open");
				return (1);
			}
		}
		else
		{
			fd = open(cmd->infile, O_RDONLY);
			if (fd < 0)
			{
				perror("open infile");
				return (1);
			}
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open outfile");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (cmd->heredoc && cmd->infile)
	{
		if (create_heredoc(cmd->infile) != 0)
			return (1);
		fd = open(HEREDOC_FILE, O_RDONLY);
		if (fd < 0)
		{
			perror("heredoc open for reading");
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	create_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc open");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}
