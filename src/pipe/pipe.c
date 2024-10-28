/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:51:25 by mkakizak          #+#    #+#             */
/*   Updated: 2024/10/28 12:45:48 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(char *input, char **cmd_arr, int *pipefd, char **envp)
{
	int		infile_fd;
	char	*cmd;

	infile_fd = open(input, O_RDONLY);
	if (infile_fd == -1)
	{
		ft_free_all(cmd_arr);
		throw_error("bash: could not find input file", EXIT_FAILURE, 0);
	}
	close(pipefd[INPUT]);
	if (dup2(pipefd[OUTPUT], STDOUT_FILENO) == -1)
		throw_error("bash: dup2 has failed", EXIT_FAILURE, 0);
	close(pipefd[OUTPUT]);
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		throw_error("bash: dup2 has failed", EXIT_FAILURE, 0);
	close(infile_fd);
	cmd = ft_strdup(cmd_arr[0]);
	ft_free_all(cmd_arr);
	// execute_cmd(cmd);
	return (0);
}

int	parent_process(char *output, char **cmd_arr, int *pipefd, char **envp)
{
	int		outfile_fd;
	char	*cmd;

	outfile_fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		ft_free_all(cmd_arr);
		throw_error("bash: output file not found", EXIT_FAILURE, 0);
	}
	close(pipefd[OUTPUT]);
	if (dup2(pipefd[INPUT], STDIN_FILENO) == -1)
		throw_error("bash: dup2 has failed", EXIT_FAILURE, 0);
	close(pipefd[INPUT]);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		throw_error("bash: dup2 has failed", EXIT_FAILURE, 0);
	close(outfile_fd);
	cmd = ft_strdup(cmd_arr[1]);
	ft_free_all(cmd_arr);
	// execute_cmd(cmd);
	return (0);
}
