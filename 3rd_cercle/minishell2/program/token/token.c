/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:53:32 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 23:09:31 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_token_handl_wd(t_token **t, char **ps, t_envp *l, int *after_her)
{
	char	*raw;
	char	*next;

	if (*after_her)
	{
		raw = ft_token_word_hd(ps);
		if (!raw)
		{
			ft_token_free(*t);
			return (0);
		}
		ft_token_add(t, ft_token_init(WRD, raw));
		free(raw);
		*after_her = 0;
		return (1);
	}
	next = ft_token_word(t, *ps, l);
	if (!next)
	{
		if (*t)
			ft_token_free(*t);
		return (0);
	}
	*ps = next;
	return (1);
}

static char	*ft_token_handle_operator(t_token **t, char *s, int *after_here)
{
	if (s[0] == '<' && s[1] == '<')
		*after_here = 1;
	return (ft_token_operator(t, s));
}

t_token	*ft_token(char *s, t_envp *l)
{
	t_token	*t;
	int		after_here;

	t = NULL;
	after_here = 0;
	while (*s)
	{
		while (ft_isspace((unsigned char)*s))
			s++;
		if (!*s)
			break ;
		if (ft_isoperator((unsigned char)*s))
			s = ft_token_handle_operator(&t, s, &after_here);
		else if (!ft_token_handl_wd(&t, &s, l, &after_here))
			return (NULL);
	}
	return (t);
}

t_operator	*ft_token_operator_init_table(void)
{
	static t_operator	tb[10];

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
	tb[8].s = ";";
	tb[8].type = SEMIC;
	tb[9].s = NULL;
	tb[9].type = 0;
	return (tb);
}
