/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:10:30 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/11 13:40:35 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_token	*ft_create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **head, t_token *new_token)
{
	t_token	*t;

	if (!*head)
		*head = new_token;
	else
	{
		t = *head;
		while (t->next)
			t = t->next;
		t->next = new_token;
	}
}

void	ft_free_token(t_token *lst)
{
	t_token	*t;

	while (lst)
	{
		t = lst->next;
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = t;
	}
}

void	ft_print_token(t_token *lst)
{
	t_token	*p;

	p = lst;
	while (p)
	{
		printf("[TOKEN] TYPE =>%d  VALUE =>'%s'\n", p->type, p->value);
		p = p->next;
	}
}

int	check_redirection_syntax(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_REDIR_APPEND
			|| token->type == TOKEN_HEREDOC)
		{
			if (!token->next || token->next->type != TOKEN_WORD)
			{
				fprintf(stderr,
					"minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}

int	check_token_syntax(t_token *token)
{
	t_token *prev = NULL;

	while (token)
	{
		t_token_type type = token->type;

		if ((type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
				|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC)
			&& (!token->next || token->next->type != TOKEN_WORD))
		{
			fprintf(stderr,
				"minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}

		if ((type == TOKEN_PIPE || type == TOKEN_AND_IF || type == TOKEN_OR_IF
				|| type == TOKEN_SEMICOLON || type == TOKEN_AND) && !prev)
		{
			fprintf(stderr,
				"minishell: syntax error near unexpected token `%s'\n",
				token->value);
			return (0);
		}

		if ((type == TOKEN_PIPE || type == TOKEN_AND_IF || type == TOKEN_OR_IF
				|| type == TOKEN_SEMICOLON || type == TOKEN_AND)
			&& (!token->next || token->next->type != TOKEN_WORD))
		{
			fprintf(stderr,
				"minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}

		if (prev && (prev->type >= TOKEN_PIPE && prev->type <= TOKEN_BACKGROUND)
			&& (type >= TOKEN_PIPE && type <= TOKEN_BACKGROUND))
		{
			fprintf(stderr,
				"minishell: syntax error near unexpected token `%s'\n",
				token->value);
			return (0);
		}

		prev = token;
		token = token->next;
	}
	return (1);
}
