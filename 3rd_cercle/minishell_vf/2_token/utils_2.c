/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:04 by codk              #+#    #+#             */
/*   Updated: 2025/10/26 17:51:19 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_token_add(t_type t, size_t i)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(*tk));
	if (!tk)
		return (NULL);
	tk->str = (char *)malloc(i + 1);
	if (!tk->str)
		return (free(tk), NULL);
	tk->type = t;
	tk->next = NULL;
	tk->str[0] = '\0';
	return (tk);
}

void	ft_token_append(t_token **hd, t_token **tl, t_token *tk)
{
	if (!tk)
		return ;
	if (!*hd)
	{
		*hd = tk;
		*tl = tk;
	}
	else
	{
		(*tl)->next = tk;
		*tl = tk;
	}
}

size_t	ft_token_wordlen(t_character *ch)
{
	t_character	*t;
	size_t		i;

	t = ch;
	i = 0;
	while (t && ch->word_id == t->word_id && !(t->type == PIPE
			|| t->type == APPEND || t->type == HEREDOC || t->type == REDIR_IN
			|| t->type == REDIR_OUT))
	{
		i++;
		t = t->next;
	}
	return (i);
}
