/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ope_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:24 by codk              #+#    #+#             */
/*   Updated: 2025/08/16 17:23:02 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_token_ope(t_token **l, char *s)
{
	t_token	*n;

	n = NULL;
	if (*s == '>' && s[1] == '>')
	{
		n = ft_token_init(R_APPEND, ">>");
		s++;
	}
	else if (*s == '>')
		n = ft_token_init(R_OUT, ">");
	else if (*s == '<' && s[1] == '<')
	{
		n = ft_token_init(HERE, "<<");
		s++;
	}
	else if (*s == '<')
		n = ft_token_init(R_IN, "<");
	else if (*s == '|' && s[1] == '|')
	{
		n = ft_token_init(OR_IF, "||");
		s++;
	}
	else if (*s == '|')
		n = ft_token_init(PIPE, "|");
	else if (*s == '&' && s[1] == '&')
	{
		n = ft_token_init(AND_IF, "&&");
		s++;
	}
	else if (*s == '&')
		n = ft_token_init(AND, "&");
	if (n)
		ft_token_add(l, n);
	return (s++);
}

int	ft_token_ope_dollar(t_envp *l, char **w, char *s, int i)
{
	char	*t;
	int		j;
	char	*r;
	char	*v;
	t_envp	*n;

	r = NULL;
	i++;
	if (s[i] == '?')
	{
		t = ft_itoa(g_exit_status);
		if (!t)
			return (i + 1);
		r = ft_strjoin(*w, t);
		free(*w);
		free(t);
		*w = r;
		return (i + 1);
	}
	if (!ft_isalpha(s[i]) && s[i] != '_')
	{
		if (ft_isdigit(s[i]))
			return (i + 1);
		t = ft_strjoin(*w, "$");
		free(*w);
		*w = t;
		return (i);
	}
	j = i;
	if (ft_isalpha(s[i]) || s[i] == '_')
	{
		i++;
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
	}
	v = ft_strndup(s + j, i - j);
	if (!v)
		return (i);
	n = ft_env_search_node(l, v);
	if (n && n->value)
		t = ft_strjoin(*w, n->value);
	else
		t = ft_strdup(*w);
	free(*w);
	free(v);
	*w = t;
	return (i);
}
