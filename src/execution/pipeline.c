/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:02 by minoka            #+#    #+#             */
/*   Updated: 2024/12/11 15:05:51 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	setup_pipes(int *prev_pipe, t_command *current, t_fd *fd)
{
	if (*prev_pipe != -1)
	{
		dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	if (current->next)
	{
		close(fd->pipe_fd[INPUT]);
		dup2(fd->pipe_fd[OUTPUT], STDOUT_FILENO);
		close(fd->pipe_fd[OUTPUT]);
	}
	return (0);
}

int	clean_pipes(int *prev_pipe, t_command *current, t_fd *fd)
{
	if (*prev_pipe != -1)
	{
		close(*prev_pipe);
	}
	if (current->next)
	{
		close(fd->pipe_fd[OUTPUT]);
		*prev_pipe = fd->pipe_fd[INPUT];
	}
	return (0);
}

void	await_process(pid_t pid, t_cmnd_tbl *table)
{
	pid_t	wpid;
	int		status;

	wpid = -1;
	while (1)
	{
		wpid = wait(&status);
		if (wpid < 0)
		{
			break ;
		}
		if (pid == wpid)
		{
			table->last_exit_status = WEXITSTATUS(status);
		}
	}
	return ;
}

void	handle_command_execution(t_command *current, t_cmnd_tbl *table,
		t_fd *fd, int *prev_pipe)
{
	pid_t	pid;
	int		is_child;

	is_child = FALSE;
	if (current->next || !current->is_built_in || has_pipe(table->head))
		pid = safe_fork(fd);
	else
		pid = -1;
	ignore_signals();
	if (pid == 0)
	{	
		init_signals(1);
		is_child = TRUE;
		redirects(current, fd, *prev_pipe);
		if (current->is_built_in)
			built_in_cmds(current, table, is_child, fd);
		else
			execute_cmd(current, table, fd);
	}
	else if (current->is_built_in && !has_pipe(table->head))
		built_in_cmds(current, table, is_child, fd);
	clean_pipes(prev_pipe, current, fd);
}

int	pipeline(t_cmnd_tbl *table)
{
	t_fd		fd;
	t_command	*current;
	int			prev_pipe;

	current = table->head;
	prev_pipe = -1;
	init_fd(&fd);
	while (current)
	{
		if (current->next)
			init_pipe(&fd);
		handle_command_execution(current, table, &fd, &prev_pipe);
		current = current->next;
	}
	await_process(-1, table);
	restore_fd(&fd);
	return (0);
}
