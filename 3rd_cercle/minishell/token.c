/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:24 by codk              #+#    #+#             */
/*   Updated: 2025/07/11 14:29:41 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_token	*ft_parse_line(char *str, t_envp *envp)
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
			i = ft_parse_word(&lst, str, i, envp);
	}
	return (lst);
}

int	ft_parse_word_double_quotes(t_envp *envp, char **word, char *line, int end,
		int i)
{
	int		start;
	char	*a;
	char	*t;

	start = i;
	while (i < end)
	{
		if (line[i] == '$')
			i = ft_parse_dollar_sign(envp, word, line, i);
		else
		{
			while (i < end && line[i] != '$')
				i++;
			t = strndup(line + start, i - start);
			a = ft_strjoin(*word, t);
			free(*word);
			free(t);
			*word = a;
		}
	}
	return (i);
}

int	ft_parse_dollar_sign(t_envp *envp, char **word, char *line, int i)
{
	char	*t;
	int		start;
	char	*value;
	char	*var;
	t_envp	*v;

	i++;
	if (line[i] == '?')
	{
		t = ft_itoa(g_exit_status);
		var = ft_strjoin(*word, t);
		free(*word);
		free(t);
		*word = var;
		return (i + 1);
	}
	start = i;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	var = strndup(line + start, i - start);
	v = ft_search_var(envp, var);
	value = v ? v->value : NULL;
	t = ft_strjoin(*word, value ? value : "");
	free(*word);
	*word = t;
	free(var);
	return (i);
}

int	ft_parse_word_without_quotes(char **word, char *line, int i)
{
	char	*a;
	char	*t;
	int		start;

	start = i;
	while (line[i] && !ft_isspace(line[i]) && !ft_isoperator(line[i])
		&& !ft_isquote(line[i]) && line[i] != '$')
		i++;
	t = strndup(line + start, i - start);
	a = ft_strjoin(*word, t);
	free(*word);
	free(t);
	*word = a;
	return (i);
}

int	ft_parse_word_single_quote(char **word, char *line, int i, int start)
{
	char	*t;
	char	*a;

	t = strndup(line + start, i - start);
	a = ft_strjoin(*word, t);
	free(*word);
	free(t);
	*word = a;
	return (i);
}

int	ft_parse_word(t_token **lst, char *line, int i, t_envp *envp)
{
	char	*word;
	char	quote;
	int		start;

	word = ft_strdup("");
	while (line[i] && !ft_isspace(line[i]) && !ft_isoperator(line[i]))
	{
		if (ft_isquote(line[i]))
		{
			quote = line[i++];
			start = i;
			while (line[i] && line[i] != quote)
				i++;
			if (quote == '"')
				i = ft_parse_word_double_quotes(envp, &word, line, i, start);
			else
				i = ft_parse_word_single_quote(&word, line, i, start);
			if (line[i])
				i++;
		}
		else if (line[i] == '$')
			i = ft_parse_dollar_sign(envp, &word, line, i);
		else
			i = ft_parse_word_without_quotes(&word, line, i);
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
			if (line[i + 2] == '>')
			{
				fprintf(stderr,
					"minishell: syntax error near unexpected token `>>'\n");
				return (-1);
			}
			token = ft_create_token(TOKEN_REDIR_APPEND, ">>");
			i++;
		}
		else
			token = ft_create_token(TOKEN_REDIR_OUT, ">");
	}
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
		{
			if (line[i + 2] == '<')
			{
				fprintf(stderr,
					"minishell: syntax error near unexpected token `<<'\n");
				return (-1);
			}
			token = ft_create_token(TOKEN_REDIR_APPEND, "<<");
			i++;
		}
		else
			token = ft_create_token(TOKEN_REDIR_IN, "<");
	}
	if (line[i] == '|')
	{
		if (line[i + 1] == '|')
		{
			// A SUPPRIMER LORS DE L'EXECUTION
			token = ft_create_token(TOKEN_OR_IF, "||");
			i++;
		}
		else
			token = ft_create_token(TOKEN_PIPE, "|");
	}
	// A SUPPRIMER LORS DE L'EXECUTION
	if (line[i] == '&')
	{
		if (line[i + 1] == '&')
		{
			token = ft_create_token(TOKEN_AND_IF, "&&");
			i++;
		}
		else
			token = ft_create_token(TOKEN_AND, "&");
	}
	ft_add_token(lst, token);
	return (i + 1);
}
