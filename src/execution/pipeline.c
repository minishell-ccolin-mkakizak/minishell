/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:02 by minoka            #+#    #+#             */
/*   Updated: 2024/10/29 15:26:00 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int output_redirect(t_command *cmd)
{
	int fd;
	int flags;

	if(cmd->output_file)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;

		fd = open(cmd->output_file, flags, 0644);
		if(fd == -1)
		{
			// need to implement error handing
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int input_redirect(t_command *cmd)
{
	int fd;
	int flags;

	if(cmd->input_file)
	{
		flags = O_RDONLY;

		fd = open(cmd->input_file, flags, 0644);
		if(fd == -1)
		{
			// need to implement error handing
			return( -1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}


int execute_pipeline(t_cmnd_tbl *table, char *envp[])
{
	t_fd 		fd;
	pid_t 		pid;
	t_command	*current;

	int 		prev_pipe;
	int			status;

	current = table->head;
	prev_pipe = -1;

	print_cmnd_tbl(table);

	// print_commands(current);

	init_fd(&fd);
	while(current)
	{
		if(current->next)
			init_pipe(&fd);

		pid = safe_fork();
		if(pid == 0)
		{
			// ft_printf("pid should be 0: %d\n", pid);
			// print_command(t)
			if(prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if(current->next)
			{
				close(fd.pipe_fd[INPUT]);
				dup2(fd.pipe_fd[OUTPUT], STDOUT_FILENO);
				close(fd.pipe_fd[OUTPUT]);
			}
			input_redirect(current);
			output_redirect(current);
			execute_cmd(current, envp);
		}

		if(prev_pipe != -1)
		{
			close(prev_pipe);
		}

		if(current->next)
		{
			close(fd.pipe_fd[OUTPUT]);
			prev_pipe = fd.pipe_fd[INPUT];
		}

		current = current->next;
	}

	while (wait(&status) > 0);
	restore_fd(&fd);
	return (0);
}