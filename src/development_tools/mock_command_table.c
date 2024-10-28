/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:27:06 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/28 10:47:55 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(const char *prompt)
{
	char	buffer[1024];

	printf("%s", prompt);
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = 0;
	return (strdup(buffer));
}

void	add_environment_variables(t_cmnd_tbl *table)
{
	int	env_count;
	int	i;

	env_count = get_env_count();
	table->envp = malloc((env_count + 1) * sizeof(char *));
	if (!table->envp)
		return ;
	i = 0;
	while (i < env_count)
	{
		table->envp[i] = get_env_variable();
		i++;
	}
	table->envp[env_count] = NULL;
}

int	get_env_count(void)
{
	int	env_count;

	printf("Enter number of environment variables: ");
	scanf("%d%*c", &env_count);
	return (env_count);
}

char	*get_env_variable(void)
{
	return (get_input("Enter environment variable (format KEY=value): "));
}

void	init_cmnd_tbl(t_cmnd_tbl *table)
{
	if (!table)
		return ;
	setup_table_defaults(table);
	handle_commands_interactive(table);
}

void	setup_table_defaults(t_cmnd_tbl *table)
{
	table->head = NULL;
	table->exit_status = 0;
	table->exit_shell = 0;
	add_environment_variables(table);
}

void	handle_commands_interactive(t_cmnd_tbl *table)
{
	char	*response;

	while (1)
	{
		add_command_interactive(table);
		response = get_input("Do you want to add another command? (yes/no): ");
		if (strcmp(response, "no") == 0)
		{
			free(response);
			break ;
		}
		free(response);
	}
}

t_command	*prompt_command(void)
{
	t_command	*cmd;

	cmd = create_command();
	if (!cmd)
		return (NULL);
	fill_command_args(cmd);
	fill_command_files(cmd);
	fill_command_flags(cmd);
	return (cmd);
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(64 * sizeof(char *));
	if (!cmd->args)
		return (NULL);
	return (cmd);
}

void	fill_command_args(t_command *cmd)
{
	char	*buffer;
	char	*arg;
	int		i;

	buffer = get_input("Enter command arguments (space-separated): ");
	i = 0;
	arg = strtok(buffer, " ");
	while (arg)
	{
		cmd->args[i++] = strdup(arg);
		arg = strtok(NULL, " ");
	}
	cmd->args[i] = NULL;
	free(buffer);
}

void	fill_command_files(t_command *cmd)
{
	cmd->input_file = get_input(
			"Enter input file (or press Enter for none): ");
	cmd->heredoc_delimiter = get_input(
			"Enter heredoc delimiter (or press Enter for none): ");
	cmd->output_file = get_input(
			"Enter output file (or press Enter for none): ");
}

void	fill_command_flags(t_command *cmd)
{
	cmd->append = atoi(get_input(
				"Append output file? (1 for yes, 0 for no): "));
	cmd->pipe_in = atoi(get_input(
				"Does this command read from a pipe? (1 for yes, 0 for no): "));
	cmd->pipe_out = atoi(get_input(
				"Does this command write to a pipe? (1 for yes, 0 for no): "));
	cmd->exec_cond = atoi(get_input(
				"Enter execution condition (0 for none, 1 for &&, 2 for ||): "));
	cmd->is_builtin = atoi(get_input(
				"Is this a built-in command? (1 for yes, 0 for no): "));
	cmd->next = NULL;
}

void	add_command_interactive(t_cmnd_tbl *table)
{
	t_command	*new_command;
	t_command	*current;

	new_command = prompt_command();
	if (!new_command)
		return ;
	if (table->head == NULL)
		table->head = new_command;
	else
	{
		current = table->head;
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
	printf("Heredoc delimiter: %s\n", cmd->heredoc_delimiter ? cmd->heredoc_delimiter : "None");
	printf("Output file: %s\n", cmd->output_file ? cmd->output_file : "None");
	printf("Append: %d\n", cmd->append);
	printf("Pipe In: %d\n", cmd->pipe_in);
	printf("Pipe Out: %d\n", cmd->pipe_out);
	printf("Execution Condition: %d\n", cmd->exec_cond);
	printf("Is Built-in: %d\n", cmd->is_builtin);
	printf("----------\n");

}

void	print_cmnd_tbl(t_cmnd_tbl *table)
{
	int	i;

	if (!table)
		return ;
	printf("Exit Status: %d\n", table->exit_status);
	printf("Exit shell: %d\n", table->exit_shell);
	// print_environment_variables(table);
	print_commands(table);
}

void	print_environment_variables(t_cmnd_tbl *table)
{
	int	i;

	printf("Environment Variables:\n");
	i = 0;
	if (table->envp)
	{
		while (table->envp[i])
		{
			printf("\tenvp[%d]: %s\n", i, table->envp[i]);
			i++;
		}
	}
	else
		printf("\tNo environment variables.\n");
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
