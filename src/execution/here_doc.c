/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:54:32 by minoka            #+#    #+#             */
/*   Updated: 2024/12/11 15:25:26 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	heredoc_iterator(t_command *cmd, int *pipe_fds)
{
	int	i;

	i = 0;
	while (cmd->heredoc_delimiter[i])
	{
		if (handle_heredoc(cmd->heredoc_delimiter[i], &pipe_fds[i * 2]) != 0)
		{
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
	return (0);
}

int	heredoc_redirect(t_command *cmd)
{
	int	i;
	int	*pipe_fds;

	if (cmd->heredoc_delimiter == NULL || cmd->heredoc_delimiter[0] == NULL)
		return (0);
	i = 0;
	while (cmd->heredoc_delimiter[i])
		i++;
	pipe_fds = malloc(sizeof(int) * (2 * i));
	if (!pipe_fds)
		return (-1);
	heredoc_iterator(cmd, pipe_fds);
	dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO);
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

int	check_for_delimiter(char *delimiter, char *input)
{
	int	input_len;
	int	delimiter_len;

	if (input == NULL || delimiter == NULL)
		return (FALSE);
	input_len = ft_strlen(input);
	delimiter_len = ft_strlen(delimiter);
	if (input_len > 0 && input[input_len - 1] == '\n')
	{
		input[input_len - 1] = '\0';
	}
	return (ft_strncmp(input, delimiter, delimiter_len + 1) == 0);
}

void	read_write_to_pipe(char *delimiter, int pipe_fd[2])
{
	char	*input;
	size_t	len;

	while (1)
	{
		write(1, ">", 1);
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			break ;
		if (check_for_delimiter(delimiter, input))
		{
			free(input);
			break ;
		}
		len = ft_strlen(input);
		if (len > 0)
		{
			if (input[len - 1] != '\n')
				input[len++] = '\n';
			write(pipe_fd[1], input, len);
		}
		free(input);
	}
	close(pipe_fd[1]);
}

int	handle_heredoc(char *delimiter, int *pipe_fd)
{
	if (delimiter == NULL)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (-1);
	read_write_to_pipe(delimiter, pipe_fd);
	return (0);
}
