/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/26 21:02:44 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* permission*/
void	print_file_error(const char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	close_if_open(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

int	ft_exec_is_directory(char *p)
{
	struct stat	st;

	if (stat(p, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

char	*ft_exec_find_cmd(char *s, t_envp *l)
{
	char	*v;
	char	**dirs;
	char	*full_path;
	int		i;

	v = ft_env_search_value(l, "PATH");
	if (!v)
		return (NULL);
	dirs = ft_split(v, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin_three(dirs[i], "/", s);
		if (full_path && access(full_path, X_OK) == 0)
		{
			ft_free_tab(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_tab(dirs);
	return (NULL);
}
