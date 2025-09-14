/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:24:59 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/14 16:42:11 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parsing	*ft_parse_add_node(t_parsing **n, t_parsing **p, t_parsing **a)
{
	t_parsing	*l;

	l = malloc(sizeof(t_parsing));
	if (!l)
		return (NULL);
	l->sep = SEP_NONE;
	l->redirs = NULL;
	l->line = NULL;
	l->next = NULL;
	l->prev = NULL;
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

	j = ft_strslen(s);
	if (!v)
		return (s);
	n = malloc(sizeof(char *) * (j + 2));
	if (!n)
		return (NULL);
	i = 0;
	while (i < j)
	{
		n[i] = s[i];
		i++;
	}
	n[j] = ft_strdup(v);
	n[j + 1] = NULL;
	free(s);
	return (n);
}

int	*ft_parse_add_append(int *s, int a)
{
	int	i;
	int	j;
	int	*n;

	i = 0;
	while (s && s[i] != -1)
		i++;
	n = malloc(sizeof(int) * (i + 2));
	if (!n)
		return (NULL);
	j = 0;
	while (j < i)
	{
		n[j] = s[j];
		j++;
	}
	n[i] = a;
	n[i + 1] = -1;
	free(s);
	return (n);
}
