/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:31:39 by codk              #+#    #+#             */
/*   Updated: 2025/09/26 17:31:48 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_token_ope(t_token **l, char *s)
{
	t_token		*n;
	t_operator	*tb;
	int			i;

	i = 0;
	n = NULL;
	tb = ft_token_ope_init_table();
	while (tb[i].s)
	{
		if (ft_strncmp(s, tb[i].s, ft_strlen(tb[i].s)) == 0)
		{
			n = ft_token_init(tb[i].type, tb[i].s);
			s += ft_strlen(tb[i].s);
			break ;
		}
		i++;
	}
	if (n)
		ft_token_add(l, n);
	return (s);
}

char	*ft_token_ope_dollar(t_envp *l, char **w, char *s)
{
	char	*t;
	char	*j;
	char	*v;
	t_envp	*n;

	if (*s == '?')
		return (ft_token_ope_dollar_interrogation(w, s));
	if (!ft_isalpha(*s) && *s != '_')
		return (ft_token_ope_dollar_no_word(w, s + 1));
	j = s;
	if (ft_isalpha(*s) || *s == '_')
		s = ft_token_ope_dollar_word(s);
	v = ft_strndup(j, s - j);
	if (!v)
		return (s);
	n = ft_env_search_node(l, v);
	if (n && n->value)
		t = ft_strjoin(*w, n->value);
	else
		t = ft_strdup(*w);
	ft_free_all(2, *w, v);
	*w = t;
	return (s);
}

char	*ft_token_ope_dollar_interrogation(char **w, char *s)
{
	char	*t;
	char	*r;

	t = ft_itoa(g_exit_status);
	if (!t)
		return (s + 1);
	r = ft_strjoin(*w, t);
	ft_free_all(2, *w, t);
	*w = r;
	return (s + 1);
}

char	*ft_token_ope_dollar_word(char *s)
{
	while (*s && (ft_isalnum(*s) || *s == '_'))
		s++;
	return (s);
}

char	*ft_token_ope_dollar_no_word(char **w, char *s)
{
	char	*t;

	if (ft_isdigit(*s))
		return (s + 1);
	t = ft_strjoin(*w, "$");
	free(*w);
	*w = t;
	return (s);
}
