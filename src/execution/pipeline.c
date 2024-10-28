/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:02 by minoka            #+#    #+#             */
/*   Updated: 2024/10/28 15:27:08 by minoka           ###   ########.fr       */
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


int execute_pipeline(t_cmnd_tbl *table, char *envp[])
{
	t_fd 		fd;
	pid_t 		pid;
	t_command	*current;

	int 		prev_pipe;
	int			status;

	current = table->head;

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
			if(prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if(current->next)
			{
				close(fd.pipe_fd[INPUT]);
				dup2(fd.pipe_fd[OUTPUT], STDOUT_FILENO);
				close(fd.pipe_fd[INPUT]);
			}
			output_redirect(table->head);
			execute_cmd(table->head, envp);
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
		puts("does it get here?");
		current = current->next;
	}

	while (wait(&status) > 0);
	restore_fd(&fd);
	return (0);
}