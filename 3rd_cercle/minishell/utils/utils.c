/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:12:08 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/01 14:34:21 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token(t_token_type type, const char *value)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->type = type;
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

void add_token(t_token **head, t_token *new_token)
{
    if (!*head)
        *head = new_token;
    else {
        t_token *curr = *head;
        while (curr->next)
            curr = curr->next;
        curr->next = new_token;
    }
}

int	ft_add_list(t_token **split_line, char *str)
{
	t_token *new_token;
	t_token *last;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(str);
		return (0);
	}
	new_token->type = TOKEN_WORD;
	new_token->value = str;
	new_token->next = NULL;

	if (*split_line == NULL)
	{
		*split_line = new_token;
	}
	else
	{
		last = *split_line;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
	return (1);
}