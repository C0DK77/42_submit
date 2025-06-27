/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:24 by codk              #+#    #+#             */
/*   Updated: 2025/06/27 18:18:02 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_word(t_token *split_line, char *line, int i)
{
	int		j;
	int		start;
	char	*word;

	(void)split_line;
	i += 1;
	start = i;
	j = 0;
	while (line[i] && !ft_issinglequote(line[i]))
		i++;
	i -= 1;
	if (ft_issinglequote(line[i + 1]))
	{
		word = malloc(sizeof(char) * (i - start + 2));
		if (!word)
			return (0);
		while (start <= i)
		{
			word[j] = line[start];
			start++;
			j++;
		}
		word[j] = '\0';
	}
	return (0);
}


void parse_double_operator(t_token tokens, char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>')
    {
        add_token(&tokens, create_token(TOKEN_REDIR_APPEND, ">>"));
        i+=2;
    }
    else if (line[i] == '<' && line[i + 1] == '<')
    {
        add_token(&tokens, create_token(TOKEN_REDIR_APPEND, ">>"));
        i+=2;
    }
    else if (line[i] == '&' && line[i + 1] == '&')
    {
        add_token(&tokens, create_token(TOKEN_AND, "&&"));
        i += 2;
    }
    else if (line[i] == '|' && line[i + 1] == '|')
    {
        add_token(&tokens, create_token(TOKEN_OR, "||"));
        i += 2;
    }
}

void parse_double_operator(t_token tokens, char *line, int i)
{
    if (line[i] == '>')
    {
        add_token(&tokens, create_token(TOKEN_REDIR_OUT, ">"));
        i++;
    }
    else if (line[i] == '<')
    {
        add_token(&tokens, create_token(TOKEN_REDIR_IN, "<"));
        i++;
    }
    else if (line[i] == '|')
    {
        add_token(&tokens, create_token(TOKEN_PIPE, "|"));
        i++;
    }
    else if (line[i] == ';')
    {
        add_token(&tokens, create_token(TOKEN_SEMICOLON, ";"));
        i++;
    }
    else if (line[i] == '(')
    {
        add_token(&tokens, create_token(TOKEN_OPEN_PAREN, "("));
        i++;
    }
    else if (line[i] == ')')
    {
        add_token(&tokens, create_token(TOKEN_CLOSE_PAREN, ")"));
        i++;
    }
}
