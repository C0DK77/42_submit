/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:10:30 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/14 15:36:10 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_init(t_token_type t, char *v)
{
	t_token	*n;

	n = malloc(sizeof(t_token));
	if (!n)
		return (NULL);
	n->type = t;
	n->value = ft_strdup(v);
	n->next = NULL;
	return (n);
}

void	ft_token_add(t_token **l, t_token *n)
{
	t_token	*t;

	if (!*l)
		*l = n;
	else
	{
		t = *l;
		while (t->next)
			t = t->next;
		t->next = n;
	}
}

t_token	*ft_token(char *s, t_envp *l)
{
	int		i;
	t_token	*t;

	i = 0;
	t = NULL;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		else if (ft_isoperator(s[i]))
			i = ft_token_ope(&t, s, i);
		else
			i = ft_token_word(&t, s, i, l);
	}
	return (t);
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
			{
				fprintf(stderr,
					"minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			if (n->next->type != WRD)
			{
				fprintf(stderr,
					"minishell: syntax error near unexpected token `%s'\n",
					n->next->value);
				return (0);
			}
		}
		if ((t == PIPE || t == AND_IF || t == OR_IF || t == SEMIC || t == AND)
			&& !prev)
		{
			fprintf(stderr,
				"minishell: syntax error near unexpected token `%s'\n",
				n->value);
			return (0);
		}
		if ((t == PIPE || t == AND_IF || t == OR_IF || t == SEMIC || t == AND)
			&& (!n->next || n->next->type != WRD))
		{
			fprintf(stderr,
				"minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}
		if (prev && (prev->type >= PIPE && prev->type <= BACKGRD) && (t >= PIPE
				&& t <= BACKGRD))
		{
			fprintf(stderr,
				"minishell: syntax error near unexpected token `%s'\n",
				n->value);
			return (0);
		}
		prev = n;
		n = n->next;
	}
	return (1);
}

void	ft_token_free(t_token *l)
{
	t_token	*t;

	while (l)
	{
		t = l->next;
		if (l->value)
			free(l->value);
		free(l);
		l = t;
	}
}
