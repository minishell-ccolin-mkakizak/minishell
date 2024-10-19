/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:16 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/19 10:59:27 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	printf("Command arguments:\n");
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("	arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
	}
	else
		printf("	No arguments.\n");
	printf("Input file: %s\n", cmd->input_file ? cmd->input_file : "None");
	printf("Output file: %s\n", cmd->output_file ? cmd->output_file : "None");
	printf("Append: %d\n", cmd->append);
	printf("Pipe In: %d\n", cmd->pipe_in);
	printf("Pipe Out: %d\n", cmd->pipe_out);
	printf("Execution Condition: %d\n", cmd->exec_cond);
	printf("Is Built-in: %d\n", cmd->is_builtin);
	printf("----------\n");
}

void	print_command_table(t_command_table *table)
{
	t_command	*current;
	int		i;

	if (!table)
		return ;
	printf("Exit Status: %d\n", table->exit_status);
	printf("Exit shell: %d\n", table->exit_shell);
	printf("Environment Variables:\n");
	if (table->envp)
	{
		i = 0;
		while (table->envp[i])
		{
			printf("	envp[%d]: %s\n", i, table->envp[i]);
			i++;
		}
	}
	else
		printf("	No environment variables.\n");
	printf("\nCommands:\n");
	current = table->head;
	while (current)
	{
		print_command(current);
		current = current->next;
	}
}

int	main_parsing(void)
{
	char			*prompt;
	char			*hostname;
	char			*input;

	ft_printf("Starting parsing mode\n");
	hostname = get_hostname();
	chdir(getenv("HOME"));
	while (1)
	{
		prompt = build_prompt(hostname);
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
	}
	clear_history();
	free(hostname);
	ft_printf("Exiting...\n");
	return (0);
}