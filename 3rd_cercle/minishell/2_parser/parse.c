/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:24 by codk              #+#    #+#             */
/*   Updated: 2025/07/03 12:12:49 by corentindes      ###   ########.fr       */
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

int	ft_parse_word_double_quotes(t_envp *envp, t_token *lst, char *line, int end,
		int i)
{
	int		start;
	char	*word;
	char	*joined;
	char	*t;

	start = i;
	while (i < end)
	{
		if (line[i] == '$')
			i = ft_parse_dollar_sign(envp, lst, line, i);
		else
		{
			while (i < end && line[i] != '$')
				i++;
			t = ft_strndup(line + start, i - start);
			joined = ft_strjoin(word, t);
			free(word);
			free(t);
			word = joined;
		}
	}
}

int	ft_parse_dollar_sign(t_envp *envp, t_token **lst, char *line, int i)
{
	int		start;
	char	*joined;
	char	*value;
	char	*var;
	char	*word;

	i++;
	start = i;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	var = ft_strndup(line + start, i - start);
	value = ft_search_var(envp, var);
	joined = ft_strjoin(word, value ? value : "");
	free(word);
	word = joined;
	free(var);
	add_token(lst, create_token(TOKEN_WORD, word));
	free(word);
	return (i);
}

int	ft_parse_word_without_quotes(t_token **lst, char *line, int i)
{
	char	*a;
	char	*t;
	char	*word;
	int		start;

	start = i;
	while (line[i] && !ft_isspace(line[i]) && !ft_isoperator(line[i])
		&& !ft_isquote(line[i]))
		i++;
	t = ft_strndup(line + start, i - start);
	a = ft_strjoin(word, t);
	free(word);
	free(t);
	word = a;
	ft_add_token(lst, ft_create_token(TOKEN_WORD, word));
	free(word);
	return (i);
}

int	ft_parse_word(t_token **lst, char *line, int i, t_envp *envp)
{
	char	*t;
	int		start;
	char	quote;
	char	*word;
	char	*joined;

	word = ft_strdup("");
	if (!word)
		return (i);
	while (line[i] && !ft_isspace(line[i]) && !ft_isoperator(line[i]))
	{
		if (ft_isquote(line[i]))
		{
			quote = line[i++];
			start = i;
			while (line[i] && line[i] != quote)
				i++;
			if (quote == '\"')
				i = ft_parse_word_double_quotes(envp, lst, line, i, start);
			if (quote == '\'')
			{
				t = ft_strndup(line + start, i - start);
				joined = ft_strjoin(word, t);
				free(word);
				free(t);
				word = joined;
			}
			if (line[i])
				i++;
		}
		else if (line[i] == '$')
			i = ft_parse_dollar_sign(envp, lst, line, i);
		else
			i = ft_parse_word_without_quotes(lst, line, i);
	}
	ft_add_token(lst, ft_create_token(TOKEN_WORD, word));
	free(word);
	return (i);
}

int	ft_parse_operator(t_token **lst, char *line, int i)
{
	t_token	*token;

	token = NULL;
	if (line[i] == '>')
	{
		if (line[i + 1] == '>')
		{
			token = ft_create_token(TOKEN_REDIR_OUT, ">>");
			i++;
		}
		else
			token = ft_create_token(TOKEN_REDIR_OUT, ">");
	}
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
		{
			token = ft_create_token(TOKEN_REDIR_OUT, "<<");
			i++;
		}
		else
			token = ft_create_token(TOKEN_REDIR_OUT, "<");
	}
	if (line[i] == '|')
		token = ft_create_token(TOKEN_PIPE, "|");
	ft_add_token(lst, token);
	return (i++);
}
