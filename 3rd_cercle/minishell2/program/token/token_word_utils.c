/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:57:51 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 23:21:25 by elisacid         ###   ########.fr       */
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

static int	push_char(char **w, char c)
{
	char	*tmp;

	tmp = ft_strndup(&c, 1);
	if (!tmp)
		return (0);
	*w = ft_strjoin_and_free(*w, tmp);
	return (*w != NULL);
}

static char	*parse_quoted(char *s, char **w, t_envp *l)
{
	char	q;

	q = *s++;
	while (*s && *s != q)
	{
		if (q == '"' && *s == '$' && *(s + 1))
		{
			if (*(s + 1) == '?')
				s = ft_token_operator_dol_interrogation(w, s + 1);
			else if (ft_isalpha(*(s + 1)) || *(s + 1) == '_')
				s = ft_token_op_dollar(l, w, s + 1);
			else if (!push_char(w, *s++))
				return (NULL);
		}
		else if (!push_char(w, *s++))
			return (NULL);
	}
	if (!*s)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching`",
			2);
		ft_putchar_fd(q, 2);
		ft_putstr_fd("'\n", 2);
		g_exit_status = 2;
		return (NULL);
	}
	return (s + 1);
}

char	*ft_token_word(t_token **n, char *s, t_envp *l)
{
	char	*w;

	w = ft_strdup("");
	if (!w)
		return (NULL);
	while (*s && !ft_isspace((unsigned char)*s)
		&& !ft_isoperator((unsigned char)*s))
	{
		if (*s == '\'' || *s == '"')
		{
			s = parse_quoted(s, &w, l);
			if (!s)
				return (free(w), NULL);
		}
		else if (*s == '$' && *(s + 1))
		{
			if (*(s + 1) == '?')
				s = ft_token_operator_dol_interrogation(&w, s + 1);
			else if (ft_isalpha(*(s + 1)) || *(s + 1) == '_')
				s = ft_token_op_dollar(l, &w, s + 1);
			else if (!push_char(&w, *s++))
				return (free(w), NULL);
		}
		else if (!push_char(&w, *s++))
			return (free(w), NULL);
	}
	ft_token_add(n, ft_token_init(WRD, w));
	return (free(w), s);
}
