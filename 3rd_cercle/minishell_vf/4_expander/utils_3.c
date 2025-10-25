/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:35:25 by codk              #+#    #+#             */
/*   Updated: 2025/10/25 07:26:29 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_special_var(void)
{
	char	*var;

	var = malloc(sizeof(char) * 2);
	if (!var)
		return (NULL);
	var[0] = '?';
	var[1] = '\0';
	return (var);
}

char	*extract_normal_var(char *str, int j, int *new_pos)
{
	char	*var;
	int		var_len;
	int		k;

	var_len = strlen_variable(str, j);
	var = malloc(sizeof(char) * (var_len + 1));
	if (!var)
		return (NULL);
	k = 0;
	while (valid_variable_char(str[j]))
		var[k++] = str[j++];
	var[k] = '\0';
	*new_pos = j - 1;
	return (var);
}

void	*cleanup_variables(char **variable, int index)
{
	while (--index >= 0)
		free(variable[index]);
	return (free(variable), NULL);
}



void	*cleanup_vars_pos(t_var_pos *vars, int index)
{
	while (--index >= 0)
		free(vars[index].name);
	return (free(vars), NULL);
}
