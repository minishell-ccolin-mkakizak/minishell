/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:45:11 by minoka            #+#    #+#             */
/*   Updated: 2024/11/18 15:51:10 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	throw_error(char *message, int exit_status, int error_number)
{
	if (error_number)
		errno = error_number;
	perror(message);
	exit(exit_status);
}

pid_t	safe_fork(void)
{
	pid_t	res;

	res = fork();
	if (res == -1)
		throw_error("bash: creating child process failed", EXIT_FAILURE, EINTR);
	return (res);
}

void init_fd(t_fd *fd)
{
	fd->stdin_backup = dup(STDIN_FILENO);
	fd->stdout_backup = dup(STDOUT_FILENO);
	fd->pipe_fd[0] = -1;
	fd->pipe_fd[1] = -1;
}

void restore_fd(t_fd *fd)
{
	dup2(fd->stdin_backup, STDIN_FILENO);
	dup2(fd->stdout_backup, STDOUT_FILENO);
	close(fd->stdin_backup);
	close(fd->stdout_backup);
}

void init_pipe(t_fd *fd)
{
	if(pipe(fd->pipe_fd) == -1)
	{
		//pipe fail error handeling
		puts("pipe creation failed");
		return ;
	}
}

int has_pipe(t_command *head)
{
	t_command *current = head;
	while (current)
	{
		if (current->next)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}
