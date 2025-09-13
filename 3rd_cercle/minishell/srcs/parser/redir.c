/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:02:04 by ecid              #+#    #+#             */
/*   Updated: 2025/09/13 20:06:02 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_redir_add(t_redir *list, t_redir_type type, char *target)
{
	t_redir	*new;
	t_redir	*tmp;
	int		q;
	char	*clean;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (list);
	new->type = type;
	new->fd = -1;
	new->hd_quoted = 0;
	new->next = NULL;
	if (type == REDIR_HEREDOC)
	{
		clean = heredoc_clean_target(target, &q);
		if (!clean)
			return (free(new), list);
		new->target = clean;
		new->hd_quoted = q;
	}
	else
	{
		new->target = ft_strdup(target);
		if (!new->target)
			return (free(new), list);
	}
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (list);
}

int	ft_handle_redirection(t_parsing *n, t_token **t)
{
	t_token	*l;

	l = *t;
	if (!l->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		return (1);
	}
	if (l->next->type != WRD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		return (ft_putstr_fd(l->next->value, 2), ft_putstr_fd("'\n", 2), 1);
	}
	ft_redirection_type(n, l->type, l->next->value);
	*t = l->next;
	return (0);
}

void	ft_redirection_type(t_parsing *n, int t, char *f)
{
	if (t == R_IN)
		n->redirs = ft_redir_add(n->redirs, REDIR_IN, f);
	else if (t == R_OUT)
		n->redirs = ft_redir_add(n->redirs, REDIR_OUT, f);
	else if (t == R_APPEND)
		n->redirs = ft_redir_add(n->redirs, REDIR_APPEND, f);
	else if (t == HERE)
		n->redirs = ft_redir_add(n->redirs, REDIR_HEREDOC, f);
}
