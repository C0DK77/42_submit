/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:24:59 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/18 21:39:58 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_parsing	*ft_parse_add_node(t_parsing **n, t_parsing **p, t_parsing **a)
{
	t_parsing	*l;

	l = calloc(1, sizeof(t_parsing));
	if (!l)
		return (NULL);
	l->sep = SEP_NONE;
	if (!*a)
		*a = l;
	if (*p)
	{
		(*p)->next = l;
		l->prev = *p;
	}
	*p = l;
	*n = l;
	return (l);
}

char	**ft_parse_add_value(char **s, char *v)
{
	int		i;
	int		j;
	char	**n;

	i = 0;
	j = ft_strslen(s);
	if (!v)
		return (s);
	n = malloc(sizeof(char *) * (j + 2));
	if (!n)
		return (NULL);
	while (i < j)
	{
		n[i] = s[i];
		i++;
	}
	n[j] = ft_strdup(v);
	n[j + 1] = NULL;
	return (free(s), n);
}
