/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:10:30 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/18 17:50:21 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_token_isquote(t_envp *l, char *w, char *s)
{
	char	quote;
	char	*start;

	quote = *s;
	s++;
	start = s;
	while (*s && *s != quote)
		s++;
	if (quote == '"')
		ft_token_word_dbquote(l, &w, start, s - start);
	else
		ft_token_word_sgquote(&w, start, s - start);
	if (*s)
		s++;
	return (s);
}

int	ft_token_check(t_token *n)
{
	t_token			*prev;
	t_token_type	t;

	prev = NULL;
	while (n)
	{
		t = n->type;
		if ((t == R_IN || t == R_OUT || t == R_APPEND || t == HERE))
		{
			if (!n->next)
				return (fprintf(stderr,
						"minishell: syntax error near unexpected token `newline'\n"),
					0);
			if (n->next->type != WRD)
				return (fprintf(stderr,
						"minishell: syntax error near unexpected token `%s'\n",
						n->next->value), 0);
		}
		if ((t == PIPE || t == AND_IF || t == OR_IF || t == SEMIC || t == AND)
			&& !prev)
			return (fprintf(stderr,
					"minishell: syntax error near unexpected token `%s'\n",
					n->value), 0);
		if ((t == PIPE || t == AND_IF || t == OR_IF || t == SEMIC || t == AND)
			&& (!n->next || n->next->type != WRD))
			return (fprintf(stderr,
					"minishell: syntax error near unexpected token `newline'\n"),
				0);
		if (prev && (prev->type >= PIPE && prev->type <= BACKGRD) && (t >= PIPE
				&& t <= BACKGRD))
			return (fprintf(stderr,
					"minishell: syntax error near unexpected token `%s'\n",
					n->value), 0);
		prev = n;
		n = n->next;
	}
	return (1);
}
