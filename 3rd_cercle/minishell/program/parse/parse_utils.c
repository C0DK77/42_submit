/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:24:59 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/30 15:49:04 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_parsing	*ft_parse_add_node(t_parsing **parse, t_parsing **p, t_parsing **a)
{
	t_parsing	*t;

	t = calloc(1, sizeof(t_parsing));
	if (!t)
		return (NULL);
	t->sep = SEP_NONE;
	t->line = NULL;
	t->next = NULL;
	t->prev = NULL;
	if (!*a)
		*a = t;
	if (*p)
	{
		(*p)->next = t;
		t->prev = *p;
	}
	*p = t;
	*parse = t;
	return (t);
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

int	*ft_parse_add_append(int *s, int a)
{
	int	i;
	int	j;
	int	*n;

	i = 0;
	j = 0;
	while (s && s[i] != -1)
		i++;
	n = malloc(sizeof(int) * (i + 2));
	if (!n)
		return (NULL);
	while (j < i)
	{
		n[j] = s[j];
		j++;
	}
	n[i] = a;
	n[i + 1] = -1;
	return (free(s), n);
}
