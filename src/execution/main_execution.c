/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:04:40 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/28 10:54:08 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_execution(char *envp[])
{
	t_cmnd_tbl	*table;

	pid_t		pid;
	table = ft_calloc(sizeof table, 1);
	if(!table)
		return (-1);

	ft_printf("Starting execution mode\n-------------\n\n");

	table->head = create_mock_commands();
	// print_cmnd_tbl(table);


	// jsut going to be excuteing one command here::
	pid = safe_fork();
	if(pid == 0)
		execute_cmd(table->head, envp);

	free_commands(table->head);
	free(table);
	return (0);
}
