/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:24 by codk              #+#    #+#             */
/*   Updated: 2025/07/02 19:38:39 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_line(char *str)
{
	int		i;
	t_token	*lst;

	i = 0;
	lst = NULL;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		else if (ft_isoperator(str[i]))
			i = ft_parse_operator(&lst, str, i);
		else
			i = ft_parse_word(&lst, str, i);
	}
}

int	ft_parse_word(t_token **lst, char *line, int i)
{
	int		start;
	int		j;
	char	*word;
	char	c;

	j = 0;
	start = i;
	if (line[i] == '\'' || line[i] == '\"')
	{
		c = line[i];
		i++;
		while (line[i] && line[i] != c)
			i++;
		if (line[i] != c)
			return (0);
	}
	else 
	{
		
	}
	word = malloc(sizeof(char) * (i - start + 1));
	if (!word)
		return (0);
	while (start < i)
		word[j++] = line[start++];
	word[j] = '\0';
	return (word);
	return (i);
}

char	*ft_word(char *line, int start, int end)
{
}

int	ft_parse_operator(t_token **lst, char *line, int i)
{
	t_token	*token;

	token = NULL;
	if (line[i] == '>')
	{
		if (line[i + 1] == '>')
		{
			token = create_token(TOKEN_REDIR_OUT, ">>");
			i++;
		}
		else
			token = create_token(TOKEN_REDIR_OUT, ">");
	}
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
		{
			token = create_token(TOKEN_REDIR_OUT, "<<");
			i++;
		}
		else
			token = create_token(TOKEN_REDIR_OUT, "<");
	}
	if (line[i] == '|')
		token = create_token(TOKEN_PIPE, "|");
	add_token(lst, token);
	return (i++);
}

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
		return (0);
	word = malloc(sizeof(char) * (i - start + 1));
	if (!word)
		return (0);
	while (start < i)
		word[j++] = line[start++];
	word[j] = '\0';
	return (word);
}
