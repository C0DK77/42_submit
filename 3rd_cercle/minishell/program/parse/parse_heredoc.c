/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 08:43:37 by codk              #+#    #+#             */
/*   Updated: 2025/09/29 10:10:27 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_parse_heredoc(t_envp *env, t_parsing *parse, char *s)
{
	int		fd[2];
	char	*l;
	char	*expanded;

	if (pipe(fd) == -1)
		return ;
	while (1)
	{
		l = readline("> ");
		if (!l)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF (wanted `",
				2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (ft_strcmp(l, s) == 0)
		{
			free(l);
			break ;
		}
		expanded = ft_expand_variables(l, env);
		write(fd[1], expanded, ft_strlen(expanded));
		write(fd[1], "\n", 1);
		free(l);
		free(expanded);
	}
	close(fd[1]);
	parse->heredoc_fd = fd[0];
}

char	*ft_expand_variables(char *s, t_envp *env)
{
	char *start;
	start = s;
	char *curr;
	curr = s;
	char *var_start = curr;
	char *var_name;
	char *v;

	char *res;
	res = ft_strdup("");
	while (*curr)
	{
		if (*curr == '$' && ft_isalpha(*(curr + 1)))
		{
			if (start != curr)
				res = ft_strjoin_free(res, ft_substr(start, 0, curr - start));
			curr++;
			while (ft_isalnum(*curr) || *curr == '_')
				curr++;
			var_name = ft_substr(var_start, 0, curr - var_start);
			v = ft_env_search_value(env, var_name);
			if (v)
				res = ft_strjoin_free(res, ft_strdup(v));
			free(var_name);
			start = curr;
		}
		else
			curr++;
	}
	if (*start)
		res = ft_strjoin_free(res, ft_strdup(start));
	return (res);
}