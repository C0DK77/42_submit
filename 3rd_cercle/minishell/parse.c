/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:26 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/07 21:37:38 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_parsing	*ft_parsing_line(t_token *t)
{
	t_parsing	*head;
	t_parsing	*current;
	t_parsing	*prev;

	head = NULL;
	current = NULL;
	prev = NULL;
	printf("[DEBUG] Entered ft_parsing_line\n");
	while (t)
	{
		printf("[DEBUG] Token: type=%d, value=%s\n", t->type, t->value);
		if (!current)
		{
			current = calloc(1, sizeof(t_parsing));
			if (!current)
			{
				printf("[ERROR] calloc failed\n");
				return (NULL);
			}
			if (!head)
				head = current;
			if (prev)
				prev->next = current;
		}
		// Vérifie que t->value est bien non NULL avant strdup
		if (t->type == TOKEN_WORD && t->value)
			current->line = ft_append_token(current->line, t->value);
		else if ((t->type == TOKEN_REDIR_IN || t->type == TOKEN_REDIR_OUT
				|| t->type == TOKEN_REDIR_APPEND || t->type == TOKEN_HEREDOC)
			&& (!t->next || !t->next->value))
		{
			printf("[ERROR] Redirection sans valeur après le token\n");
			return (NULL);
		}
		else if (t->type == TOKEN_REDIR_IN)
		{
			t = t->next;
			current->infile = ft_strdup(t->value);
		}
		else if (t->type == TOKEN_REDIR_OUT)
		{
			t = t->next;
			current->outfile = ft_strdup(t->value);
			current->append = 0;
		}
		else if (t->type == TOKEN_REDIR_APPEND)
		{
			t = t->next;
			current->outfile = ft_strdup(t->value);
			current->append = 1;
		}
		else if (t->type == TOKEN_HEREDOC)
		{
			t = t->next;
			current->infile = ft_strdup(t->value);
			current->heredoc = 1;
		}
		else if (t->type == TOKEN_PIPE)
		{
			current->sep = SEP_PIPE;
			prev = current;
			current = NULL;
		}
		else if (t->type == TOKEN_AND_IF)
		{
			current->sep = SEP_AND_IF;
			prev = current;
			current = NULL;
		}
		else if (t->type == TOKEN_OR_IF)
		{
			current->sep = SEP_OR_IF;
			prev = current;
			current = NULL;
		}
		else if (t->type == TOKEN_AND)
		{
			current->sep = SEP_BACKGROUND;
			prev = current;
			current = NULL;
		}
		else if (t->type == TOKEN_SEMICOLON)
		{
			current->sep = SEP_SEQ;
			prev = current;
			current = NULL;
		}
		t = t->next;
	}
	return (head);
}
