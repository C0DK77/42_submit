/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:35:25 by codk              #+#    #+#             */
/*   Updated: 2025/10/26 07:30:08 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_expander_extract_var(char *s, t_var_pos *var, int i, int j)
{
	int	len;
	int	k;

	var->start = i;
	len = ft_expander_len_var(s, j);
	var->name = malloc(sizeof(char) * (len + 1));
	if (!var->name)
		return (-1);
	k = 0;
	while (ft_isalpha(s[j]) || s[j] == '_' || (k > 0 && (ft_isalnum(s[j])
				|| s[j] == '_')))
		var->name[k++] = s[j++];
	var->name[k] = '\0';
	var->end = j;
	return (j - 1);
}

int	ft_expander_len_var(char *s, int j)
{
	int	i;

	i = 0;
	if (s[j] == '?')
		return (1);
	while (s[j] && (ft_isalpha(s[j]) || s[j] == '_'))
	{
		i++;
		j++;
	}
	return (i);
}
