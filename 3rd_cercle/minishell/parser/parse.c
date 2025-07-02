/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:24 by codk              #+#    #+#             */
/*   Updated: 2025/07/01 14:25:44 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_word_issinglequote(char *line, int i)
{
	int		j;
	int		start;
	char	*word;

	i += 1;
	start = i;
	j = 0;
	while (line[i] && !ft_issinglequote(line[i]))
		i++;
	if (!ft_issinglequote(line[i]))
	{
		printf("Erreur pas de deuxieme quote");
		return (0);
	}
	word = malloc(sizeof(char) * (i - start + 1));
	if (!word)
		return (0);
	while (start < i)
		word[j++] = line[start++];
	word[j] = '\0';
	return (word);
}

int	ft_parse_word_isdoublequote(char *line, int i)
{
	int		j;
	int		start;
	char	*word;

	i += 1;
	start = i;
	j = 0;
	while (line[i] && !ft_isdoublequote(line[i]))
		i++;
	if (!ft_isdoublequote(line[i]))
	{
		printf("Erreur pas de deuxieme quote");
		return (0);
	}
	word = malloc(sizeof(char) * (i - start + 1));
	if (!word)
		return (0);
	while (start < i)
		word[j++] = line[start++];
	word[j] = '\0';
	return (word);
}

int	ft_parse_word_withoutquotes(char *line, int i)
{
	int		j;
	int		start;
	char	*word;

	i += 1;
	start = i;
	j = 0;
	while (line[i] && !ft_isspace(line[i]) && !ft_isoperator(line[i]))
		i++;
	word = malloc(sizeof(char) * (i - start + 1));
	if (!word)
		return (0);
	while (start < i)
		word[j++] = line[start++];
	word[j] = '\0';
	return (word);
}

void parse_operator(char *line, int i)
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
