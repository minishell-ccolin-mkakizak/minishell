/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command_tables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:27:06 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/19 17:52:16 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_arrays(char **array, char *arg_type)
{
	int	i;

	printf("Command %s:\n", arg_type);
	if (array)
	{
		i = 0;
		while (array[i])
		{
			printf("\t%s[%d]: %s\n", arg_type, i, array[i]);
			i++;
		}
	}
	else
		printf("\tNo %s.\n", arg_type);
}

void	print_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	print_command_arrays(cmd->args, "arg");
	print_command_details(cmd);
}

void	print_command_details(t_command *cmd)
{
	printf("Input file: %s\n", cmd->input_file ? cmd->input_file : "None");
	printf("Heredoc delimiter: %s\n", cmd->heredoc_delimiter ? cmd->heredoc_delimiter : "None");
	print_command_arrays(cmd->output_file, "output");
	print_command_arrays(cmd->append, "append");
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
