/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:31:39 by codk              #+#    #+#             */
/*   Updated: 2025/09/29 10:01:08 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_token_ope(t_token **token, char *s)
{
	int			i;
	t_token		*t;
	t_operator	*operator;

	i = 0;
	t = NULL;
	operator= ft_token_ope_init_table();
	while (operator[i].s)
	{
		if (ft_strncmp(s, operator[i].s, ft_strlen(operator[i].s)) == 0)
		{
			t = ft_token_init(operator[i].type, operator[i].s);
			s += ft_strlen(operator[i].s);
			break ;
		}
		i++;
	}
	if (t)
		ft_token_add(token, t);
	return (s);
}

char	*ft_token_ope_dollar(t_envp *env, char **w, char *s)
{
	char	*a;
	char	*j;
	char	*v;
	t_envp	*t;

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
	t = ft_env_search_node(env, v);
	if (t && t->value)
		a = ft_strjoin(*w, t->value);
	else
		a = ft_strdup(*w);
	ft_free_all(2, *w, v);
	*w = a;
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
