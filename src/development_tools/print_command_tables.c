/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command_tables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:27:06 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/18 16:54:23 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	print_command_args(cmd);
	print_command_details(cmd);
}

void	print_command_args(t_command *cmd)
{
	int	i;

	printf("Command arguments:\n");
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("\targ[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
	}
	else
		printf("\tNo arguments.\n");
}

void	print_command_details(t_command *cmd)
{
	printf("Input file: %s\n", cmd->input_file ? cmd->input_file : "None");
	printf("Heredoc delimiter: %s\n",
		cmd->heredoc_delimiter ? cmd->heredoc_delimiter : "None");
	printf("Output file: %s\n", cmd->output_file ? cmd->output_file : "None");
	printf("Append: %s\n", cmd->append);
	printf("Pipe In: %d\n", cmd->pipe_in);
	printf("Pipe Out: %d\n", cmd->pipe_out);
	printf("Is Built-in: %d\n", cmd->is_built_in);
	printf("----------\n\n");
}

void	print_cmnd_tbl(t_cmnd_tbl *table)
{
	int	i;
	if (!TABLE_DEBUG)
		return ;
	if (!table)
		return ;
	printf("Exit Status: %d\n", table->exit_status);
	printf("Exit shell: %d\n", table->exit_shell);
	// print_environment_variables(table);
	print_commands(table);
}

void	print_commands(t_cmnd_tbl *table)
{
	t_command	*current;

	printf("\nCommands:\n");
	current = table->head;
	while (current)
	{
		print_command(current);
		current = current->next;
	}
}
