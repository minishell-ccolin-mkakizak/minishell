/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/02 17:13:49 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_command_table(t_cmnd_tbl **command_table, char *envp[])
{
	*command_table = malloc(sizeof(t_cmnd_tbl));
	if (!*command_table)
		return (alloc_failed());
	(*command_table)->head = NULL;
	(*command_table)->exit_shell = 0;
	(*command_table)->last_exit_status = 0;
	(*command_table)->envp = init_env(envp);
	return (0);
}

void	init_command(t_command *command, int is_pipe)
{
	if (!command)
		return ;
	command->command = NULL;
	command->args = NULL;
	command->input_file = NULL;
	command->output_file = NULL;
	command->heredoc_delimiter = NULL;
	command->append = NULL;
	if (is_pipe)
		command->pipe_in = 1;
	else
		command->pipe_in = 0;
	command->last_input_heredoc = 0;
	command->last_output_append = 0;
	command->pipe_out = 0;
	command->is_built_in = 0;
	command->next = NULL;
}

int	init_new_command(t_command **command, int is_pipe)
{
	*command = malloc(sizeof(t_command));
	if (!*command)
		return (alloc_failed());
	init_command(*command, is_pipe);
	return (0);
}
