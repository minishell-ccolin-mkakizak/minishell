/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:15:13 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/13 12:42:55 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_all_digits(const char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (FALSE);
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	exit_with_error_numeric(t_command *cmd)
{
	printf("minishell: exit: %s:", cmd->args[0]);
	printf(" numeric argument required\n");
	exit(2);
}

void	exe_exit(t_command *cmd, t_cmnd_tbl *table)
{
	unsigned int	exit_status;
	unsigned int	exit_status;

	exit_status = 0;
	printf("exit\n");
	exit_status = 0;
	exit_status = ft_atoi(cmd->args[0]);
	printf("exit_status: %d\n", exit_status);
	if (cmd->args[0] == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	if (!is_all_digits(cmd->args[0]))
		exit_with_error_numeric(cmd);
	exit_status = (unsigned int)atoi(cmd->args[0]);
	if (cmd->args[1] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		if (table)
			table->last_exit_status = EXIT_FAILURE;
		return ;
	}
	exit(exit_status);
}
