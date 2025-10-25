/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:35:31 by codk              #+#    #+#             */
/*   Updated: 2025/10/25 07:35:32 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	extract_special_var_pos(t_var_pos *var, int start, int j)
{
	var->start = start;
	var->name = malloc(sizeof(char) * 2);
	if (!var->name)
		return (-1);
	var->name[0] = '?';
	var->name[1] = '\0';
	var->end = j + 1;
	return (j);
}

int	extract_variable_pos(char *str, t_var_pos *var, int start, int j)
{
	int	var_len;
	int	k;

	var->start = start;
	var_len = strlen_variable(str, j);
	var->name = malloc(sizeof(char) * (var_len + 1));
	if (!var->name)
		return (-1);
	k = 0;
	while (valid_variable_char(str[j]) || (k > 0
			&& valid_variable_char_number(str[j])))
		var->name[k++] = str[j++];
	var->name[k] = '\0';
	var->end = j;
	return (j - 1);
}

