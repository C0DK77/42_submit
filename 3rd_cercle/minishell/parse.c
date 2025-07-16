/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:26 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/16 18:05:20 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**ft_parse_add(char **s, char *v)
{
	int		i;
	char	**n;

	i = 0;
	if (!v)
		return (s);
	while (s && s[i])
		i++;
	n = malloc(sizeof(char *) * (i + 2));
	if (!n)
		return (NULL);
	for (int j = 0; j < i; j++)
		n[j] = s[j];
	n[i] = ft_strdup(v);
	n[i + 1] = NULL;
	free(s);
	return (n);
}

t_parsing	*ft_parse_line(t_token *t)
{
	t_parsing	*a;
	t_parsing	*n;
	t_parsing	*prev;

	a = NULL;
	n = NULL;
	prev = NULL;
	while (t)
	{
		if (!n)
		{
			n = calloc(1, sizeof(t_parsing));
			if (!n)
				return (NULL);
			n->sep = SEP_NONE;
			if (!a)
				a = n;
			if (prev)
				prev->next = n;
		}
		if (t->type == WRD && t->value)
			n->line = ft_parse_add(n->line, t->value);
		else if ((t->type == R_IN || t->type == R_OUT || t->type == R_APPEND
				|| t->type == HERE) && (!t->next || !t->next->value))
			return (NULL);
		else if (t->type == R_IN)
		{
			t = t->next;
			n->infile = ft_strdup(t->value);
		}
		else if (t->type == R_OUT)
		{
			t = t->next;
			n->outfile = ft_strdup(t->value);
			n->append = 0;
		}
		else if (t->type == R_APPEND)
		{
			t = t->next;
			n->outfile = ft_strdup(t->value);
			n->append = 1;
		}
		else if (t->type == HERE)
		{
			t = t->next;
			n->infile = ft_strdup(t->value);
			n->heredoc = 1;
		}
		else if (t->type == PIPE)
		{
			n->sep = SEP_PIPE;
			prev = n;
			n = NULL;
		}
		else if (t->type == AND_IF)
		{
			n->sep = SEP_AND_IF;
			prev = n;
			n = NULL;
		}
		else if (t->type == OR_IF)
		{
			n->sep = SEP_OR_IF;
			prev = n;
			n = NULL;
		}
		else if (t->type == AND)
		{
			n->sep = SEP_BACKGROUND;
			prev = n;
			n = NULL;
		}
		else if (t->type == SEMIC)
		{
			n->sep = SEP_SEQ;
			prev = n;
			n = NULL;
		}
		t = t->next;
	}
	return (a);
}
