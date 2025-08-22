/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/22 19:50:15 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
    t_envp *c_envp;

    (void)argc;
    (void)argv;

    setbuf(stdout, NULL);

    c_envp = ft_env_list_init(envp);
    if (!c_envp)
        return (1);
    if (!ft_env_vars_check(&c_envp))
        return (0);

    signal(SIGINT, ft_sigint_handler);
    signal(SIGQUIT, SIG_IGN);

    while (1)
    {
        if (!ft_program(c_envp))
            break;
    }

    ft_env_free(c_envp);
    return (0);
}

int ft_program(t_envp *c_envp)
{
    char       *line;
    t_token    *tokens;
    t_parsing  *parse;

    line = readline(ft_env_prompt());
    if (!line)
    {
        printf("exit\n");
        return (0);
    }
    if (*line)
        add_history(line);

    tokens = ft_token(line, c_envp);
    if (!tokens || !ft_token_check(tokens))
    {
        ft_token_free(tokens);
        free(line);
        return (1);
    }

    parse = ft_parse_line(tokens);

    ft_token_free(tokens);
    free(line);

    if (!parse)
        return (1);

    ft_exec(parse, c_envp); 


    return (1);
}

