/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:10:30 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 17:30:13 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_token	*ft_token(char *s, t_envp *l)
{
	int		i;
	t_token	*t;

	i = 0;
	t = NULL;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (!(*s))
			break ;
		else if (ft_isoperator(*s))
			s = ft_token_ope(&t, s);
		else
			s = ft_token_word(&t, s, l);
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
