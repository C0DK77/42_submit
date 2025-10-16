/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:04 by codk              #+#    #+#             */
/*   Updated: 2025/10/15 20:46:27 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isoperator_type(t_type type)
{
	if (type == PIPE || type == APPEND || type == HEREDOC || type == REDIR_IN
		|| type == REDIR_OUT)
		return (1);
	return (0);
}

int	valid_variable_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	ft_is_samewrd(t_character *a, t_character *b)
{
	if (a->word_id != b->word_id)
		return (0);
	return (1);
}

t_token	*new_token(t_type type, size_t len)
{
	t_token	*tkn;

	tkn = (t_token *)malloc(sizeof(*tkn));
	if (!tkn)
		return (NULL);
	tkn->str = (char *)malloc(len + 1);
	if (!tkn->str)
	{
		free(tkn);
		return (NULL);
	}
	tkn->type = type;
	tkn->next = NULL;
	tkn->str[0] = '\0';
	return (tkn);
}

void	append_token(t_token **head, t_token **tail, t_token *node)
{
	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		*tail = node;
	}
	else
	{
		(*tail)->next = node;
		*tail = node;
	}
}
