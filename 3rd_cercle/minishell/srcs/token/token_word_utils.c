/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:57:51 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/24 21:10:40 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_token_word(t_token **n, char *s, t_envp *l)
{
	char	*w;

	w = ft_strdup("");
	while (*s && !ft_isspace(*s) && !ft_isoperator(*s))
	{
		if (ft_isquote(*s))
			s = ft_token_isquote(l, &w, s);
		else if (*s == '$')
			s = ft_token_operator_dollar(l, &w, s + 1);
		else
			s = ft_token_word_noquote(&w, s);
	}
	ft_token_add(n, ft_token_init(WRD, w));
	free(w);
	return (s);
}

char	*ft_token_word_dbquote(t_envp *l, char **w, char *s, char *end)
{
	char	*i;
	char	*a;
	char	*t;

	while (s < end)
	{
		if (*s == '$')
			s = ft_token_operator_dollar(l, w, s + 1);
		i = s;
		while (s < end && *s != '$')
			s++;
		t = ft_strndup(i, s - i);
		a = ft_strjoin(*w, t);
		ft_free_all(2, *w, t);
		*w = a;
	}
	return (s);
}

char	*ft_token_word_sgquote(char **w, char *s, char *i)
{
	char	*t;
	char	*a;

	t = ft_strndup(i, s - i);
	if (!t)
		return (s);
	a = ft_strjoin(*w, t);
	ft_free_all(2, *w, t);
	*w = a;
	return (s);
}

int	ft_token_word_len(char *s)
{
	int	i;

	i = 0;
	//changement ici
	while (s && *s && !ft_isspace((unsigned char)*s) && !ft_isoperator(*s) && !ft_isquote(*s))
	{
		if (*s == '\\' && *(s + 1))
		{
			s += 2;
			i += 2;
		}
		else
		{
			s++;
			i++;
		}
	}
	return (i);
}

char	*ft_token_word_noquote(char **w, char *s)
{
	char	*t;
	char	*res;
	char	*start;
	int		i;

	start = s;
	t = malloc(ft_token_word_len(s) + 1);
	if (!t)
		return (start);
	s = start;
	i = 0;
	while (*s && !ft_isspace(*s) && !ft_isoperator(*s) && !ft_isquote(*s))
	{
		if (*s == '\\' && *(s + 1))
			s++;
		t[i++] = *s++;
	}
	t[i] = '\0';
	res = ft_strjoin(*w, t);
	ft_free_all(2, *w, t);
	*w = res;
	return (s);
}
