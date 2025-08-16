/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ope_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:24 by codk              #+#    #+#             */
/*   Updated: 2025/08/16 21:02:01 by corentindes      ###   ########.fr       */
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
	free(tb);
	if (n)
		ft_token_add(l, n);
	return (s);
}

t_operator	*ft_token_ope_init_table(void)
{
	static t_operator	tb[9];

	tb[0].s = ">>";
	tb[0].type = R_APPEND;
	tb[1].s = ">";
	tb[1].type = R_OUT;
	tb[2].s = "<<";
	tb[2].type = HERE;
	tb[3].s = "<";
	tb[3].type = R_IN;
	tb[4].s = "||";
	tb[4].type = OR_IF;
	tb[5].s = "|";
	tb[5].type = PIPE;
	tb[6].s = "&&";
	tb[6].type = AND_IF;
	tb[7].s = "&";
	tb[7].type = AND;
	tb[8].s = NULL;
	tb[8].type = 0;
	return (tb);
}

int	ft_token_ope_dollar(t_envp *l, char **w, char *s, int i)
{
	char	*t;
	int		j;
	char	*v;
	t_envp	*n;

	i++;
	if (s[i] == '?')
		i = ft_token_ope_dollar_interrogation(w, i);
	if (!ft_isalpha(s[i]) && s[i] != '_')
		i = ft_token_ope_dollar_no_word(w, s, i);
	j = i;
	if (ft_isalpha(s[i]) || s[i] == '_')
		i = ft_token_ope_dollar_word(s, i);
	v = ft_strndup(s + j, i - j);
	if (!v)
		return (i);
	n = ft_env_search_node(l, v);
	if (n && n->value)
		t = ft_strjoin(*w, n->value);
	else
		t = ft_strdup(*w);
	ft_free_all(*w, v);
	*w = t;
	return (i);
}

int	ft_token_ope_dollar_interrogation(char **w, int i)
{
	char	*t;
	char	*r;

	r = NULL;
	t = ft_itoa(g_exit_status);
	if (!t)
		return (i + 1);
	r = ft_strjoin(*w, t);
	ft_free_all(*w, t);
	*w = r;
	return (i + 1);
}

int	ft_token_ope_dollar_word(char *s, int i)
{
	i++;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

int	ft_token_ope_dollar_no_word(char **w, char *s, int i)
{
	char	*t;

	if (ft_isdigit(s[i]))
		return (i + 1);
	t = ft_strjoin(*w, "$");
	free(*w);
	*w = t;
	return (i);
}
