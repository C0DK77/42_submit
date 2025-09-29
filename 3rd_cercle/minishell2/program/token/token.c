/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:53:32 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 21:03:27 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token(char *s, t_envp *l)
{
	t_token	*t;
	int		after_here;
	char	*raw;
	char	*next;

	t = NULL;
	after_here = 0;
	while (*s)
	{
		while (ft_isspace((unsigned char)*s))
			s++;
		if (!(*s))
			break ;
		else if (ft_isoperator((unsigned char)*s))
		{
			if (s[0] == '<' && s[1] == '<')
				after_here = 1;
			s = ft_token_operator(&t, s);
		}
		else
		{
			if (after_here)
			{
				raw = ft_token_word_hd(&s);
				if (!raw)
				{
					ft_token_free(t);
					return (NULL);
				}
				ft_token_add(&t, ft_token_init(WRD, raw));
				free(raw);
				after_here = 0;
			}
			else
			{
				next = ft_token_word(&t, s, l);
				if (!next)
				{
					if (t)
						ft_token_free(t);
					return (NULL);
				}
				s = next;
			}
		}
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
