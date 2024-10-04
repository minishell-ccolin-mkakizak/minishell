/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:51:25 by mkakizak          #+#    #+#             */
/*   Updated: 2024/10/03 07:40:13 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(char *cmd, char *envp[])
{
	char	**cmd_arr;
	char	*path;

	cmd_arr = ft_split(cmd, ' ');
	free(cmd);
	path = find_path(cmd_arr[0], envp);
	if (!path)
	{
		free_all(cmd_arr);
		free(path);
		throw_error("bash: command not found", 127, 0);
	}
	if (execve(path, cmd_arr, envp) == -1)
	{
		free_all(cmd_arr);
		free(path);
		throw_error("bash: execution went worng", EXIT_FAILURE, 0);
	}
	return (0);
}

int	child_process(char *input, char **cmd_arr, int *pipefd, char **envp)
{
	int		infile_fd;
	char	*cmd;

	infile_fd = open(input, O_RDONLY);
	if (infile_fd == -1)
	{
		free_all(cmd_arr);
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
	free_all(cmd_arr);
	execute_cmd(cmd, envp);
	return (0);
}

int	parent_process(char *output, char **cmd_arr, int *pipefd, char **envp)
{
	int		outfile_fd;
	char	*cmd;

	outfile_fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		free_all(cmd_arr);
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
	free_all(cmd_arr);
	execute_cmd(cmd, envp);
	return (0);
}

pid_t	safe_fork(void)
{
	pid_t	res;

	res = fork();
	if (res == -1)
		throw_error("bash: creating child process failed", EXIT_FAILURE, EINTR);
	return (res);
}

int	my_pipe(int argc, char *argv[], char *envp[])
{
	char	**cmd_arr;
	int		pipefd[2];
	pid_t	first_pid;
	pid_t	last_pid;
	int		status;

	cmd_arr = parse_cmd(argc, argv);
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	first_pid = safe_fork();
	if (first_pid == 0)
		child_process(argv[1], cmd_arr, pipefd, envp);
	last_pid = safe_fork();
	if (last_pid == 0)
		parent_process(argv[argc - 1], cmd_arr, pipefd, envp);
	close(pipefd[INPUT]);
	close(pipefd[OUTPUT]);
	free_all(cmd_arr);
	if (waitpid(last_pid, &status, 0) == -1)
		exit(EXIT_FAILURE);
	if (waitpid(first_pid, NULL, 0) == -1)
		exit(EXIT_FAILURE);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (0);
}
