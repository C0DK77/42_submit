/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:12:08 by corentindes       #+#    #+#             */
/*   Updated: 2025/06/27 18:12:33 by corentindes      ###   ########.fr       */
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