/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:07:41 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/17 12:10:32 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
// checking for out files and chaning commands
t_command *create_mock_commands_0(void)
{
    t_command *first, *second, *third;
    // Allocate memory for commands
    first = malloc(sizeof(t_command));
    second = malloc(sizeof(t_command));
    third = malloc(sizeof(t_command));

    // First command: "ls -la > output.txt"
    first->args = malloc(sizeof(char *) * 3);
    first->args[0] = strdup("/usr/bin/ls");
    first->args[1] = strdup("-l");
    first->args[2] = NULL;
    first->input_file = NULL;
    first->output_file = NULL;
    // first->output_file = strdup("output.txt");
    first->heredoc_delimiter = NULL;
    first->append = NULL;
    first->pipe_in = 0;
    first->pipe_out = 0;
    first->is_built_in = 0;
    first->next = second;

    // Second command?: "grep 'hello' < input.txt | "
    second->args = malloc(sizeof(char *) * 3);
    second->args[0] = strdup("grep");
    second->args[1] = strdup("2020");
    second->args[2] = NULL;
    // second->input_file = strdup("input.txt");
    second->input_file = NULL;
    // second->output_file = NULL;
    second->output_file = strdup("hello.txt");
    second->heredoc_delimiter = NULL;
    second->append = NULL;
    second->pipe_in = 0;
    second->pipe_out = 1;
    second->is_built_in = 0;
    second->next = third;

    // Third command: "wc -l >> count.txt"
    third->args = malloc(sizeof(char *) * 3);
    third->args[0] = strdup("ls");
    third->args[1] = NULL;
    third->args[2] = NULL;
    third->input_file = NULL;
    // third->output_file = strdup("output.txt");
    third->output_file = NULL;
    third->heredoc_delimiter = NULL;
    third->append = NULL;
    third->pipe_in = 1;
    third->pipe_out = 0;
    third->is_built_in = 0;
    third->next = NULL;

    return (first);
}

// checking for pipes
t_command *create_mock_commands_1(void)
{
    t_command *first, *second, *third;
    // Allocate memory for commands
    first = malloc(sizeof(t_command));
    second = malloc(sizeof(t_command));
    third = malloc(sizeof(t_command));

    // First command: "ls -la > output.txt"
    first->args = malloc(sizeof(char *) * 3);
    first->args[0] = strdup("cat");
    first->args[1] = NULL;
    first->args[2] = NULL;
    first->input_file = strdup("test.txt");
    first->output_file = NULL;
    // first->output_file = strdup("output.txt");
    first->heredoc_delimiter = NULL;
    first->append = NULL;
    first->pipe_in = 0;
    first->pipe_out = 0;
    first->is_built_in = 0;
    first->next = second;

    // Second command?: "grep 'hello' < input.txt | "
    second->args = malloc(sizeof(char *) * 3);
    second->args[0] = strdup("cat");
    second->args[1] = NULL;
    second->args[2] = NULL;
    // second->input_file = strdup("input.txt");
    second->input_file = NULL;
    second->output_file = NULL;
    second->heredoc_delimiter = NULL;
    second->append = NULL;
    second->pipe_in = 0;
    second->pipe_out = 1;
    second->is_built_in = 0;
    second->next = third;

    // Third command: "wc -l >> count.txt"
    third->args = malloc(sizeof(char *) * 3);
    third->args[0] = strdup("cat");
    third->args[1] = NULL;
    third->args[2] = NULL;
    third->input_file = NULL;
    third->output_file = strdup("outfile.txt");
    third->heredoc_delimiter = NULL;
    third->append = NULL;
    third->pipe_in = 1;
    third->pipe_out = 0;
    third->is_built_in = 0;
    third->next = NULL;

    return (first);
}

// testing for here docW
t_command *create_mock_commands_2(void)
{
    t_command *first;
    // Allocate memory for commands
    first = malloc(sizeof(t_command));
    // second = malloc(sizeof(t_command));
    // third = malloc(sizeof(t_command));

    // First command: "ls -la > output.txt"
    first->args = malloc(sizeof(char *) * 3);
    first->args[0] = strdup("cat");
    first->args[1] = NULL;
    first->args[2] = NULL;
    first->input_file = NULL;
    first->output_file = NULL;
    // first->output_file = strdup("output.txt");
    first->heredoc_delimiter = strdup("heredoc");
    first->append = 0;
    first->pipe_in = 0;
    first->pipe_out = 0;
    first->is_built_in = 0;
    first->next = NULL;

    return (first);
}

void free_commands(t_command *cmd)
{
    t_command *temp;
    int i;

    while (cmd)
    {
        temp = cmd->next;

        // Free args array
        i = 0;
        while (cmd->args && cmd->args[i])
            free(cmd->args[i++]);
        free(cmd->args);

        // Free other allocated strings
        free(cmd->input_file);
        free(cmd->output_file);
        free(cmd->heredoc_delimiter);

        // Free the command structure itself
        free(cmd);
        cmd = temp;
    }
}


// mock parsing is for built in commands can only do one command at a time
t_command *mock_parsing(char *input)
{
	t_command	*cmd;
	char 		**cmd_array;

    // Allocate memory for commands
    cmd = malloc(sizeof(t_command));

	cmd_array =  ft_split(input, ' ');

    // First command: ""
    cmd->args = malloc(sizeof(char *) * 3);
    cmd->args[0] = ft_strdup(cmd_array[0]);
    cmd->args[1] = ft_strdup(cmd_array[1]);
    cmd->args[2] = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    // cmd->output_file = strdup("output.txt");
    cmd->heredoc_delimiter = NULL;
    cmd->append = 0;
    cmd->pipe_in = 0;
    cmd->pipe_out = 0;
    cmd->is_built_in = 1;
    cmd->next = NULL;

    ft_free_all(cmd_array);
	ft_printf("%s\n", input);


	return (cmd);
}