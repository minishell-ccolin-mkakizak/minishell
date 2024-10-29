/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:04:40 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/29 14:47:09 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_execution(char *envp[])
{
	t_cmnd_tbl	*table;
	pid_t		pid;
	int 		outfile_fd;

	table = ft_calloc(sizeof(t_cmnd_tbl), 1);
	if(!table)
		return (-1);

	ft_printf("Starting execution mode\n-------------\n\n");

	table->head = create_mock_commands();
	table->exit_shell = 0;
	table->exit_status = 0;
	table->envp = NULL;
	// print_cmnd_tbl(table);

	// jsut going to be excuteing one command here:

	execute_pipeline(table, envp);

	// pid = safe_fork();
	// if(pid == 0)
	// 	execute_cmd(table->head, envp);

	free_commands(table->head);
	free(table);
	return (0);
}
