/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:02 by minoka            #+#    #+#             */
/*   Updated: 2024/11/19 17:14:18 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int output_redirect(t_command *cmd)
{
	int fd;
	int flags;

	if(cmd->output_file)
	{
		// this needs an if condition if the operation is > or >>
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

	if(cmd->heredoc_delimiter)
	{
		handle_heredoc(cmd);
		return(0);
	}

	if(cmd->input_file)
	{
		// this also needs a if statment if the operation is < or <<
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

int setup_pipes(int *prev_pipe, t_command *current, t_fd *fd)
{
	if(*prev_pipe != -1)
	{
		dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	if(current->next)
	{
		close(fd->pipe_fd[INPUT]);
		dup2(fd->pipe_fd[OUTPUT], STDOUT_FILENO);
		close(fd->pipe_fd[OUTPUT]);
	}
	return (0);
}

int clean_pipes(int *prev_pipe, t_command *current, t_fd *fd)
{
	if(*prev_pipe != -1)
		{
			close(*prev_pipe);
		}

		if(current->next)
		{
			close(fd->pipe_fd[OUTPUT]);
			*prev_pipe = fd->pipe_fd[INPUT];
		}
		return (0);
}

int	pipeline(t_cmnd_tbl *table, char *envp[])
{
	//maybe i can add some of these to the table struct
	t_fd 		fd;
	pid_t 		pid;
	t_command	*current;
	int 		is_child;

	int 		prev_pipe;
	int			status;

	current = table->head;
	prev_pipe = -1;

	init_fd(&fd);

	is_child = FALSE;
	pid = 1;

	while(current)
	{

		if(current->next)
			init_pipe(&fd);

		if(current->next || !current->is_built_in || has_pipe(table->head))
		pid = safe_fork();

		if(pid == 0)
		{
			is_child = TRUE;
			setup_pipes(&prev_pipe, current, &fd);
			input_redirect(current);
			output_redirect(current);

			if(current->is_built_in)
				built_in_cmds(current, table->envp, is_child);
			else
				execute_cmd(current, envp, is_child);
		}
		else if (current->is_built_in && !has_pipe(table->head))
		{
			built_in_cmds(current, table->envp, is_child);
		}
		clean_pipes(&prev_pipe, current, &fd);
		current = current->next;
	}
	while (wait(&status) > 0);
	restore_fd(&fd);
	return (0);
}
