/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:10:30 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/04 10:28:21 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_check_operator(char c)
{
	if (c == ';' || c == '&' || c == '(' || c == ')')
	{
		printf("Operateur pas pris en compte par le sujet.");
		return (0);
	}
	return (1);
}

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
