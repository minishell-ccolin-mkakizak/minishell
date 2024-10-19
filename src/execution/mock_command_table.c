/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:27:06 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/19 16:02:56 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_environment_variables(t_command_table *table)
{
	int	env_count;
	printf("Enter number of environment variables: ");
	scanf("%d%*c", &env_count);
	table->envp = malloc((env_count + 1) * sizeof(char *));
	if (!table->envp)
		return;

	for (int i = 0; i < env_count; i++)
	{
		char *env = get_input("Enter environment variable (format KEY=value): ");
		table->envp[i] = env;
	}
	table->envp[env_count] = NULL;
}

char *get_input(const char *prompt)
{
	char	buffer[1024];
	printf("%s", prompt);
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = 0;
	return strdup(buffer);
}

void	init_command_table(t_command_table *table)
{
	if (!table)
		return;

	table->head = NULL;
	table->exit_status = 0;
	table->exit_shell = 0;
	add_environment_variables(table);

	while (1)
	{
		add_command_interactive(table);
		char *response = get_input("Do you want to add another command? (yes/no): ");
		if (strcmp(response, "no") == 0)
		{
			free(response);
			break;
		}
		free(response);
	}
	printf("\n\n");
}

t_command *prompt_command(void)
{
	t_command *cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);

	cmd->args = malloc(64 * sizeof(char *));
	if (!cmd->args)
		return (NULL);

	char *buffer = get_input("Enter command arguments (space-separated): ");
	int i = 0;
	char *arg = strtok(buffer, " ");
	while (arg)
	{
		cmd->args[i++] = strdup(arg);
		arg = strtok(NULL, " ");
	}
	cmd->args[i] = NULL;
	free(buffer);
	char *input = get_input("Enter input file (or press Enter for none): ");
	cmd->input_file = strlen(input) > 0 ? input : NULL;
	char *output = get_input("Enter output file (or press Enter for none): ");
	cmd->output_file = strlen(output) > 0 ? output : NULL;
	free(output);
	char *buffer_flag = get_input("Append output file? (1 for yes, 0 for no): ");
	cmd->append = atoi(buffer_flag);
	free(buffer_flag);
	buffer_flag = get_input("Does this command read from a pipe? (1 for yes, 0 for no): ");
	cmd->pipe_in = atoi(buffer_flag);
	free(buffer_flag);
	buffer_flag = get_input("Does this command write to a pipe? (1 for yes, 0 for no): ");
	cmd->pipe_out = atoi(buffer_flag);
	free(buffer_flag);
	buffer_flag = get_input("Enter execution condition (0 for none, 1 for &&, 2 for ||): ");
	cmd->exec_cond = atoi(buffer_flag);
	free(buffer_flag);
	buffer_flag = get_input("Is this a built-in command? (1 for yes, 0 for no): ");
	cmd->is_builtin = atoi(buffer_flag);
	free(buffer_flag);
	cmd->next = NULL;
	return (cmd);
}

void	add_command_interactive(t_command_table *table)
{
	t_command *new_command = prompt_command();
	if (!new_command)
		return;

	if (table->head == NULL)
		table->head = new_command;
	else
	{
		t_command *current = table->head;
		while (current->next)
			current = current->next;
		current->next = new_command;
	}
}

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
	int			i;

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