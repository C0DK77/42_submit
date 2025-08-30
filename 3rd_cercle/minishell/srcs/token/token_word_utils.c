/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:57:51 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/30 20:32:44 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_token_word(t_token **n, char *s, t_envp *l)
{
	char	*w;
	int		in_single_quotes;
	int		in_double_quotes;

	w = ft_strdup("");
	in_single_quotes =0;
	in_double_quotes =0;

	while (*s && (!ft_isspace(*s) || in_single_quotes || in_double_quotes) &&(!ft_isoperator(*s) || in_single_quotes || in_double_quotes))
	{
		if(*s== '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			s++;
		}
		else if(*s== '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			s++;
		}
		else if(*s == '$' && !in_single_quotes)
			s= ft_token_operator_dollar(l, &w, s+1);
		else
		{
			char *temp = ft_strndup(s, 1);
			char *joined = ft_strjoin(w, temp);
			free(w);
			free(temp);
			w = joined;
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
// 	while (s && *s && !ft_isspace((unsigned char)*s) && !ft_isoperator(*s) && !ft_isquote(*s))
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
