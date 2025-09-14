/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:57 by ecid              #+#    #+#             */
/*   Updated: 2025/09/14 17:39:06 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	clean_core(const char *s, char *out, int *quoted)
{
	const char	*p;
	char		*w;
	char		*last;
	int			in_q;
	char		qch;

	p = s;
	while (*p == ' ' || *p == '\t')
		p++;
	w = out;
	last = out;
	in_q = 0;
	qch = 0;
	while (*p)
	{
		if (!in_q && (*p == '\'' || *p == '"'))
		{
			*quoted = 1;
			in_q = 1;
			qch = *p++;
			continue ;
		}
		if (in_q && *p == qch)
		{
			in_q = 0;
			p++;
			continue ;
		}
		*w++ = *p;
		if (in_q || !(*p == ' ' || *p == '\t'))
			last = w;
		p++;
	}
	return ((size_t)(last - out));
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
