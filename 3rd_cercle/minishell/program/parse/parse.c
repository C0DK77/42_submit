/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:26 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/30 14:45:06 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_handle_redirection(t_envp *env, t_token **token, t_parsing *parse)
{
	t_token	*t;
	char	*delimiter;

	t = *token;
	if (!t->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `lline'\n",
			2);
		return (1);
	}
	if (t->next->type != WRD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		return (ft_putstr_fd(t->next->value, 2), ft_putstr_fd("'\n", 2), 1);
	}
	if (t->type == HERE)
	{
		if (is_quoted(t->next->value))
			parse->heredoc_expand = 0;
		else
			parse->heredoc_expand = 1;
		delimiter = remove_quotes(t->next->value);
		parse->infiles = ft_parse_add_value(parse->infiles, delimiter);
		parse->heredoc = 1;
		ft_parse_heredoc(env, parse, delimiter);
		free(delimiter);
	}
	else
		ft_redirection_type(env, parse, t->next->value, t->type);
	*token = t->next;
	return (0);
}

void	ft_redirection_type(t_envp *env, t_parsing *parse, char *s, int i)
{
	(void)env;
	if (i == R_IN)
		parse->infiles = ft_parse_add_value(parse->infiles, s);
	else if (i == R_OUT || i == R_APPEND)
	{
		parse->outfiles = ft_parse_add_value(parse->outfiles, s);
		parse->append = ft_parse_add_append(parse->append, (i == R_APPEND));
	}
}

t_parsing	*ft_parse_line(t_envp *env, t_token *token)
{
	t_parsing	*a;
	t_parsing	*n;
	t_parsing	*p;

	a = NULL;
	n = NULL;
	p = NULL;
	while (token)
	{
		if (!n && !ft_parse_add_node(&n, &p, &a))
			return (NULL);
		if (token->type == WRD && token->value)
			n->line = ft_parse_add_value(n->line, token->value);
		else if ((token->type == R_IN || token->type == R_OUT
				|| token->type == R_APPEND || token->type == HERE)
			&& ft_handle_redirection(env, &token, n))
			return (NULL);
		ft_parse_type(token, n);
		if (token->type == PIPE || token->type == AND_IF || token->type == OR_IF
			|| token->type == AND || token->type == SEMIC)
			n = NULL; 
		token = token->next;
	}
	return (a);
}

void	ft_parse_type(t_token *token, t_parsing *parse)
{
	if (!parse || !token)
		return ;
	if (token->type == PIPE)
		parse->sep = SEP_PIPE;
	else if (token->type == AND_IF)
		parse->sep = SEP_AND_IF;
	else if (token->type == OR_IF)
		parse->sep = SEP_OR_IF;
	else if (token->type == AND)
		parse->sep = SEP_BACKGROUND;
	else if (token->type == SEMIC)
		parse->sep = SEP_SEQ;
}
