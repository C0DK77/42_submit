/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:24 by codk              #+#    #+#             */
/*   Updated: 2025/07/22 12:04:33 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_token_word_dbquote(t_envp *l, char **w, char *s, int z, int i)
{
	int		j;
	char	*a;
	char	*t;

	j = i;
	while (i < z)
	{
		if (s[i] == '$')
			i = ft_token_ope_dollar(l, w, s, i);
		else
		{
			while (i < z && s[i] != '$')
				i++;
			t = ft_strndup(s + j, i - j);
			a = ft_strjoin(*w, t);
			free(*w);
			free(t);
			*w = a;
		}
	}
	return (i);
}

int	ft_token_ope_dollar(t_envp *l, char **w, char *s, int i)
{
	char	*t;
	int		j;
	char	*r;
	char	*v;
	t_envp	*n;

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
	j = i;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (i == j)
	{
		t = ft_strjoin(*w, "$");
		free(*w);
		*w = t;
		return (i);
	}
	v = ft_strndup(s + j, i - j);
	if (!v)
		return (i);
	r = NULL;
	n = ft_env_search_node(l, v);
	if (n && n->value)
		r = n->value;
	if (r)
		t = ft_strjoin(*w, r);
	else
		t = ft_strjoin(*w, "");
	free(*w);
	free(v);
	*w = t;
	return (i);
}

int	ft_token_word_noquote(char **w, char *s, int i)
{
	char	*tmp;
	int		start;
	char	*result;
	int		j;

	// int		len;
	start = i;
	// len = 0;
	while (s[i] && !ft_isspace(s[i]) && !ft_isoperator(s[i])
		&& !ft_isquote(s[i]))
	{
		if (s[i] == '\\' && s[i + 1])
			i += 2;
		else
			i++;
	}
	tmp = malloc(i - start + 1);
	if (!tmp)
		return (i);
	i = start;
	j = 0;
	while (s[i] && !ft_isspace(s[i]) && !ft_isoperator(s[i])
		&& !ft_isquote(s[i]))
	{
		if (s[i] == '\\' && s[i + 1])
		{
			i++;
			tmp[j++] = s[i++];
		}
		else
			tmp[j++] = s[i++];
	}
	tmp[j] = '\0';
	result = ft_strjoin(*w, tmp);
	free(*w);
	free(tmp);
	*w = result;
	return (i);
}

int	ft_token_word_sgquote(char **w, char *s, int i, int j)
{
	char	*t;
	char	*a;

	t = ft_strndup(s + j, i - j);
	a = ft_strjoin(*w, t);
	free(*w);
	free(t);
	*w = a;
	return (i);
}

int	ft_token_word(t_token **n, char *s, int i, t_envp *l)
{
	char	*w;
	char	quote;
	int		j;

	w = ft_strdup("");
	while (s[i] && !ft_isspace(s[i]) && !ft_isoperator(s[i]))
	{
		if (ft_isquote(s[i]))
		{
			quote = s[i++];
			j = i;
			while (s[i] && s[i] != quote)
				i++;
			if (quote == '"')
				i = ft_token_word_dbquote(l, &w, s, i, j);
			else
				i = ft_token_word_sgquote(&w, s, i, j);
			if (s[i])
				i++;
		}
		else if (s[i] == '$')
			i = ft_token_ope_dollar(l, &w, s, i);
		else
			i = ft_token_word_noquote(&w, s, i);
	}
	ft_token_add(n, ft_token_init(WRD, w));
	free(w);
	return (i);
}

int	ft_token_ope(t_token **l, char *s, int i)
{
	t_token	*n;

	n = NULL;
	if (s[i] == '>')
	{
		if (s[i + 1] == '>')
		{
			if (s[i + 2] == '>')
			{
				fprintf(stderr,
					"minishell: syntax error near unexpected token `>>'\n");
				return (-1);
			}
			n = ft_token_init(R_APPEND, ">>");
			i++;
		}
		else
			n = ft_token_init(R_OUT, ">");
	}
	else if (s[i] == '<')
	{
		if (s[i + 1] == '<')
		{
			if (s[i + 2] == '<')
			{
				fprintf(stderr,
					"minishell: syntax error near unexpected token `<<'\n");
				return (-1);
			}
			n = ft_token_init(HERE, "<<");
			i++;
		}
		else
			n = ft_token_init(R_IN, "<");
	}
	else if (s[i] == '|')
	{
		if (s[i + 1] == '|')
		{
			n = ft_token_init(OR_IF, "||");
			i++;
		}
		else
			n = ft_token_init(PIPE, "|");
	}
	else if (s[i] == '&')
	{
		if (s[i + 1] == '&')
		{
			n = ft_token_init(AND_IF, "&&");
			i++;
		}
		else
			n = ft_token_init(AND, "&");
	}
	ft_token_add(l, n);
	return (i + 1);
}
