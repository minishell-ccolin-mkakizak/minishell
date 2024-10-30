/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:04:40 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/30 17:11:51 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_execution(char *envp[])
{

	t_cmnd_tbl	*table;
	pid_t		pid;
	int 		outfile_fd;

	// these are for mock parsing
	char		*prompt;
	char		*hostname;
	char		*input;

	table = ft_calloc(sizeof(t_cmnd_tbl), 1);
	if(!table)
		return (-1);

	ft_printf("Starting execution mode\n-------------\n\n");

	//This is for dev purposes only just making a simple parser to do built in commands
	hostname = get_hostname();
	// chdir(getenv("HOME"));
	while (1)
	{
		prompt = build_prompt(hostname);
		input = readline(prompt);
		if (!input)
		{
			free(prompt);
			break ;
		}
		free(prompt);
		table->head = mock_parsing(input);
		table->exit_shell = 0;
		table->exit_status = 0;
		table->envp = NULL;
		execute_pipeline(table, envp);
		free(input);
	}
	clear_history();
	free(hostname);
	ft_printf("Exiting...\n");

	// print_cmnd_tbl(table);
	//running pipeline
	// execute_pipeline(table, envp);

	// this will not be freed when its hooked up;
	ft_printf("Ending execution mode\n-------------\n\n");
	free_commands(table->head);
	free(table);
	return (0);
}
