/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:07:41 by mkakizak          #+#    #+#             */
/*   Updated: 2024/10/29 15:27:35 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
    first->append = 0;
    first->pipe_in = 0;
    first->pipe_out = 0;
    first->exec_cond = 0;
    first->is_builtin = 0;
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
    second->append = 0;
    second->pipe_in = 0;
    second->pipe_out = 1;
    second->exec_cond = 0;
    second->is_builtin = 0;
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
    third->append = 1;
    third->pipe_in = 1;
    third->pipe_out = 0;
    third->exec_cond = 0;
    third->is_builtin = 0;
    third->next = NULL;

    return (first);
}

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
    first->append = 0;
    first->pipe_in = 0;
    first->pipe_out = 0;
    first->exec_cond = 0;
    first->is_builtin = 0;
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
    second->append = 0;
    second->pipe_in = 0;
    second->pipe_out = 1;
    second->exec_cond = 0;
    second->is_builtin = 0;
    second->next = third;

    // Third command: "wc -l >> count.txt"
    third->args = malloc(sizeof(char *) * 3);
    third->args[0] = strdup("cat");
    third->args[1] = NULL;
    third->args[2] = NULL;
    third->input_file = NULL;
    third->output_file = NULL;
    third->heredoc_delimiter = NULL;
    third->append = 1;
    third->pipe_in = 1;
    third->pipe_out = 0;
    third->exec_cond = 0;
    third->is_builtin = 0;
    third->next = NULL;

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