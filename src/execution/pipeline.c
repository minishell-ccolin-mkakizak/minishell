/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:02 by minoka            #+#    #+#             */
/*   Updated: 2024/10/28 13:56:15 by minoka           ###   ########.fr       */
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
	t_fd fd;
	pid_t pid;

	init_fd(&fd);

	pid = safe_fork();
	if(pid == 0)
	{
		output_redirect(table->head);
		execute_cmd(table->head, envp);
	}

	restore_fd(&fd);
	return (0);
}