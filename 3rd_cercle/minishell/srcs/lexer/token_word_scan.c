/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_scan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:57:51 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/16 19:10:52 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_token_word_hd(char **ps)
{
	char	*s;
	int		i;
	int		in_q;
	char	qch;
	char	*out;

	s = *ps;
	i = 0;
	in_q = 0;
	qch = 0;
	while (s[i] && (!ft_isspace((unsigned char)s[i]) || in_q)
		&& (!ft_isoperator((unsigned char)s[i]) || in_q))
	{
		if (!in_q && (s[i] == '\'' || s[i] == '"'))
		{
			in_q = 1;
			qch = s[i];
		}
		else if (in_q && s[i] == qch)
			in_q = 0;
		i++;
	}
	out = ft_substr(s, 0, (size_t)i);
	if (!out)
		return (NULL);
	*ps += i;
	return (out);
}

char	*ft_token_word(t_token **n, char *s, t_envp *l)
{
	char	*w;
	char	quote;
	char	*temp;

	quote = 0;
	w = ft_strdup("");
	if (!w)
		return (NULL);
	while (*s && (!ft_isspace(*s) || quote) && (!ft_isoperator(*s) || quote))
	{
		if (*s == '\'' || *s == '"')
		{
			quote = *s++;
			while (*s && *s != quote)
			{
				if (quote == '"' && *s == '$' && *(s + 1))
				{
					if (ft_isalpha(*(s + 1)) || *(s + 1) == '_')
						s = ft_token_op_dollar(l, &w, s + 1);
					else if (*(s + 1) == '?')
						s = ft_token_operator_dollar_interrogation(&w, s + 1);
					else
					{
						temp = ft_strndup(s, 1);
						w = ft_strjoin_and_free(w, temp);
						s++;
					}
				}
				else
				{
					temp = ft_strndup(s, 1);
					w = ft_strjoin_and_free(w, temp);
					s++;
				}
			}
			if (!*s)
			{
				ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
					2);
				ft_putchar_fd(quote, 2);
				ft_putstr_fd("'\n", 2);
				g_exit_status = 2;
				free(w);
				return (NULL);
			}
			if (*s)
				s++;
			quote = 0;
		}
		else if (*s == '$' && *(s + 1))
		{
			if (ft_isalpha(*(s + 1)) || *(s + 1) == '_')
				s = ft_token_op_dollar(l, &w, s + 1);
			else if (*(s + 1) == '?')
				s = ft_token_operator_dollar_interrogation(&w, s + 1);
			else
			{
				temp = ft_strndup(s, 1);
				w = ft_strjoin_and_free(w, temp);
				s++;
			}
		}
		else
		{
			temp = ft_strndup(s, 1);
			w = ft_strjoin_and_free(w, temp);
			s++;
		}
	}
	ft_token_add(n, ft_token_init(WRD, w));
	free(w);
	return (s);
}

// char	*ft_token_word_dbquote(t_envp *l, char **w, char *s, char *end)
// {
// 	char	*i;
// 	char	*a;
// 	char	*t;

// 	while (s < end)
// 	{
// 		if (*s == '$')
// 			s = ft_token_operator_dollar(l, w, s + 1);
// 		i = s;
// 		while (s < end && *s != '$')
// 			s++;
// 		t = ft_strndup(i, s - i);
// 		a = ft_strjoin(*w, t);
// 		ft_free_all(2, *w, t);
// 		*w = a;
// 	}
// 	return (s);
// }

// char	*ft_token_word_sgquote(char **w, char *s, char *i)
// {
// 	char	*t;
// 	char	*a;

// 	t = ft_strndup(i, s - i);
// 	if (!t)
// 		return (s);
// 	a = ft_strjoin(*w, t);
// 	ft_free_all(2, *w, t);
// 	*w = a;
// 	return (s);
// }

// int	ft_token_word_len(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s && *s && !ft_isspace((unsigned char)*s) && !ft_isoperator(*s)
// && !ft_isquote(*s))
// 	{
// 		if (*s == '\\' && *(s + 1))
// 		{
// 			s += 2;
// 			i += 2;
// 		}
// 		else
// 		{
// 			s++;
// 			i++;
// 		}
// 	}
// 	return (i);
// }

// char	*ft_token_word_noquote(char **w, char *s)
// {
// 	char	*t;
// 	char	*res;
// 	char	*start;
// 	int		i;

// 	start = s;
// 	t = malloc(ft_token_word_len(s) + 1);
// 	if (!t)
// 		return (start);
// 	s = start;
// 	i = 0;
// 	while (*s && !ft_isspace(*s) && !ft_isoperator(*s) && !ft_isquote(*s))
// 	{
// 		if (*s == '\\' && *(s + 1))
// 			s++;
// 		t[i++] = *s++;
// 	}
// 	t[i] = '\0';
// 	res = ft_strjoin(*w, t);
// 	ft_free_all(2, *w, t);
// 	*w = res;
// 	return (s);
// }
