/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:54:32 by minoka            #+#    #+#             */
/*   Updated: 2024/12/09 15:35:25 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int heredoc_redirect(t_command *cmd)
{
    int i;
    int *pipe_fds;

    if (cmd->heredoc_delimiter == NULL || cmd->heredoc_delimiter[0] == NULL)
        return (0);

    // Allocate pipe file descriptors for each delimiter
    i = 0;
    while (cmd->heredoc_delimiter[i])
        i++;

    pipe_fds = malloc(sizeof(int) * (2 * i));
    if (!pipe_fds)
        return (-1);  // Memory allocation error

    i = 0;
    while (cmd->heredoc_delimiter[i])
    {
        if (handle_heredoc(cmd->heredoc_delimiter[i], &pipe_fds[i * 2]) != 0)
        {
            // Clean up previously created pipes if an error occurs
            while (i > 0)
            {
                i--;
                close(pipe_fds[i * 2]);
                close(pipe_fds[i * 2 + 1]);
            }
            free(pipe_fds);
            return (-1);
        }
        i++;
    }

    // If multiple heredocs, use the last one's pipe for stdin
    dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO);

    // Close all pipe file descriptors
    i = 0;
    while (cmd->heredoc_delimiter[i])
    {
        close(pipe_fds[i * 2]);
        close(pipe_fds[i * 2 + 1]);
        i++;
    }

    free(pipe_fds);
    return (0);
}

int check_for_delimiter(char *delimiter, char *input)
{
    int input_len;
    int delimiter_len;

    if (input == NULL || delimiter == NULL)
        return (FALSE);

    input_len = ft_strlen(input);
    delimiter_len = ft_strlen(delimiter);

    // Remove newline from input if present
    if (input_len > 0 && input[input_len - 1] == '\n')
        input[input_len - 1] = '\0';

    // Compare the input with the delimiter
    return (ft_strncmp(input, delimiter, delimiter_len + 1) == 0);
}

int handle_heredoc(char *delimiter, int *pipe_fd)
{
    char *input;
    size_t len;

    if (delimiter == NULL)
        return (-1);

    // Create pipe
    if (pipe(pipe_fd) == -1)
        return (-1);

    while (1)
    {
        ft_printf("->");
        input = get_next_line(STDIN_FILENO);

        // Handle EOF or error in get_next_line
        if (input == NULL)
        {
            // If EOF is reached without finding delimiter, still create heredoc
            break;
        }

        // Check if input matches delimiter
        if (check_for_delimiter(delimiter, input))
        {
            free(input);
            break;
        }

        // Write input to pipe
		len = ft_strlen(input);
        if (len > 0)
        {
            // Restore the newline if it was removed during delimiter check
            if (input[len - 1] != '\n')
                input[len++] = '\n';
            
            write(pipe_fd[1], input, len);
        }
        free(input);
    }

    close(pipe_fd[1]);
    return (0);
}
