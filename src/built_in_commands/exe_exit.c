/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:15:13 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/13 12:21:58 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int is_all_digits(const char *str)
{
	if (!str || *str == '\0')
		return FALSE;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!ft_isdigit(str[i]))
			return FALSE;
	}
	return (TRUE);
}

void exe_exit(t_command *cmd, t_cmnd_tbl *table)
{
    unsigned int exit_status = 0;

	printf("exit\n");
    if (!cmd || !cmd->args) {
        exit(EXIT_SUCCESS);
    }
    if (cmd->args[0] == NULL) {
        exit(EXIT_SUCCESS);
    }
    if (!is_all_digits(cmd->args[0])) 
	{
        printf("minishell: exit: %s: numeric argument required\n", cmd->args[0]);
        exit(2);
    }
    exit_status = (unsigned int)atoi(cmd->args[0]);
    if (cmd->args[1] != NULL) 
	{
        printf("minishell: exit: too many arguments\n");
        if (table)
            table->last_exit_status = EXIT_FAILURE;
        return;
    }
    exit(exit_status);
}
