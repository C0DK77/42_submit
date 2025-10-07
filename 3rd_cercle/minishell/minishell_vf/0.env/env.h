/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:32:31 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 04:32:33 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../minishell.h"

char	**init_local_env(void);
char	**copy_env(char **envp);

int		get_shlvl_value(char **envp);
char	*get_env_value_from_envp(char **envp, const char *var);
char	*get_env_value(char **env, const char *var);
int		count_env_vars(char **env);
void	add_env_var(char ***env, char *new_var);

void	set_env_var(char ***env, const char *var, const char *value);

#endif