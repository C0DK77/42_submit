/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:34:04 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 19:09:10 by corentindes      ###   ########.fr       */
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

int	ft_isoperator_type(t_type type)
{
	if (type == PIPE || type == APPEND || type == HEREDOC || type == REDIR_IN
		|| type == REDIR_OUT)
		return (1);
	return (0);
}

int	ft_isvalid_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

size_t	ft_token_wordlen(t_character *ch)
{
	t_character	*t;
	size_t		i;

	t = ch;
	i = 0;
	while (t && ft_token_sameword(ch, t) && !ft_token_isoperator(t->type))
	{
		i++;
		t = t->next;
	}
	return (i);
}
