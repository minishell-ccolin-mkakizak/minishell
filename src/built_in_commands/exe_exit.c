/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:15:13 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/12 17:33:03 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int is_all_digits(const char *str)
{
	if (!str || *str == '\0')
		return FALSE; // NULL or empty string returns false	

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!ft_isdigit(str[i]))
			return FALSE;
	}
	return (TRUE);
}

void	exe_exit(t_command *cmd, t_cmnd_tbl *table)
{
	(void)cmd;
	(void)table;
	printf("exit\n");

	unsigned int exit_status = 0;
	exit_status = atoi(cmd->args[0]);
	printf("exit_status: %d\n", exit_status);

	if (cmd->args[0] == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	else if(cmd->args[1] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		table->last_exit_status = EXIT_FAILURE;
		return ;
	}
	else if(exit_status == 0 || !is_all_digits(cmd->args[0]))
	{
		printf("minishell: exit: ");
		printf("%s: numeric argument required\n", cmd->args[0]);
		exit(2);
	}
	exit(exit_status);
}