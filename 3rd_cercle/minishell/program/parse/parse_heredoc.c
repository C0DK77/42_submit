/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 08:43:37 by codk              #+#    #+#             */
/*   Updated: 2025/09/30 17:56:27 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_parse_heredoc(t_envp *env, t_parsing *parse, char *s)
{
	int		fd[2];
	char	*l;
	char	*a;

	if (pipe(fd) == -1)
		return ;
	while (1)
	{
		l = readline("> ");
		if (!l)
		{
			ft_putall_fd(2, 3,
				"minishell: warning: heredoc delimited by EOF (wanted `", s,
				"')\n");
			break ;
		}
		if (ft_strcmp(l, s) == 0)
		{
			free(l);
			break ;
		}
		if (parse->heredoc_expand)
			a = ft_expand_variables(l, env);
		else
			a = ft_strdup(l);
		ft_putall_fd(fd[1], 2, a, "\n");
		ft_free_all(2, l, a);
	}
	close(fd[1]);
	parse->heredoc_fd = fd[0];
}

char	*ft_expand_variables(char *s, t_envp *env)
{
	char	*res;
	char	*start;
	char	*curr;
	char	*var_start;
	char	*var_name;
	char	*val;

	res = ft_strdup("");
	start = s;
	curr = s;
	while (*curr)
	{
		if (*curr == '$' && ft_isalpha(*(curr + 1)))
		{
			res = ft_strjoin_free(res, ft_substr(start, 0, curr - start));
			curr++;
			var_start = curr;
			while (ft_isalnum(*curr) || *curr == '_')
				curr++;
			var_name = ft_substr(var_start, 0, curr - var_start);
			val = ft_env_search_value(env, var_name);
			if (val)
				res = ft_strjoin_free(res, ft_strdup(val));
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

char	*remove_quotes(char *s)
{
	size_t len = ft_strlen(s);
	if ((s[0] == '\'' || s[0] == '"') && s[len - 1] == s[0])
		return (ft_substr(s, 1, len - 2));
	return (ft_strdup(s));
}