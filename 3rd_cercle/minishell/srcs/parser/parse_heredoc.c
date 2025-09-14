/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:57 by ecid              #+#    #+#             */
/*   Updated: 2025/09/14 17:48:04 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// entree/sortie quotes
int	handle_quote(int *in_q, char *qch, int *quoted, char c)
{
	if (!*in_q && (c == '\'' || c == '"'))
	{
		*quoted = 1;
		*in_q = 1;
		*qch = c;
		return (1);
	}
	if (*in_q && c == *qch)
	{
		*in_q = 0;
		return (1);
	}
	return (0);
}

size_t	clean_core_loop(const char *p, char *out, int *quoted)
{
	size_t	j;
	size_t	last;
	int		in_q;
	char	qch;

	j = 0;
	last = 0;
	in_q = 0;
	qch = 0;
	while (*p)
	{
		if (handle_quote(&in_q, &qch, quoted, *p))
		{
			p++;
			continue ;
		}
		out[j++] = *p;
		if (in_q || !(*p == ' ' || *p == '\t'))
			last = j;
		p++;
	}
	return (last);
}

size_t	clean_core(const char *s, char *out, int *quoted)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (clean_core_loop(s, out, quoted));
}

char	*heredoc_clean_target(const char *s, int *quoted)
{
	size_t	n;
	char	*out;
	size_t	len;

	if (!s)
		return (NULL);
	*quoted = 0;
	n = ft_strlen(s);
	out = (char *)malloc(n + 1);
	if (!out)
		return (NULL);
	len = clean_core(s, out, quoted);
	out[len] = '\0';
	return (out);
}
