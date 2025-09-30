/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:57:51 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/30 18:02:29 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_token_word(t_envp *env, t_token **token, char *s)
{
	char	*w;
	int		i;

	i = 0;
	w = ft_strdup("");
	while (*s && !ft_isspace(*s) && !ft_isoperator(*s))
	{
		if (ft_isquote(*s))
		{
			i = 1;
			s = ft_token_isquote(env, &w, s);
		}
		else if (*s == '$')
			s = ft_token_ope_dollar(env, &w, s + 1);
		else
			s = ft_token_word_noquote(&w, s);
	}
	if (w && *w != '\0')
		ft_token_add(token, ft_token_init(WRD, w, i));
	return (free(w), s);
}

char	*ft_token_word_dbquote(t_envp *env, char **w, char *s, char *end)
{
	char	*i;
	char	*a;
	char	*t;

	while (s < end)
	{
		if (*s == '$')
			s = ft_token_ope_dollar(env, w, s + 1);
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
	while (s && !ft_isspace((unsigned char)*s) && !ft_isoperator(*s)
		&& !ft_isquote(*s))
	{
		if (*s == '\\' && *(s + 1))
		{
			s += 2;
			i += 2;
		}
		else
			s++;
		i++;
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
