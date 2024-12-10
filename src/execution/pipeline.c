/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:02 by minoka            #+#    #+#             */
/*   Updated: 2024/12/10 15:24:22 by ccolin           ###   ########.fr       */
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
			// need to implement error handing
			break ;
		}
		if (pid == wpid)
		{
			table->last_exit_status = WEXITSTATUS(status);
		}
	}
	return ;
}

int	pipeline(t_cmnd_tbl *table, char *envp[])
{
	t_fd		fd;
	pid_t		pid;
	t_command	*current;
	int			is_child;
	int			prev_pipe;
	int			status;

	current = table->head;
	prev_pipe = -1;
	is_child = FALSE;
	pid = -1;
	init_fd(&fd);
	while (current)
	{
		if (current->next)
			init_pipe(&fd);
		if (current->next || !current->is_built_in || has_pipe(table->head))
		{
			pid = safe_fork(&fd);
		}
		if (pid == 0)
		{
			is_child = TRUE;
			redirects(current, &fd, prev_pipe);
			if (current->is_built_in)
				built_in_cmds(current, table, is_child, &fd);
			else
				execute_cmd(current, table, is_child, &fd);
		}
		else if (current->is_built_in && !has_pipe(table->head))
		{
			built_in_cmds(current, table, is_child, &fd);
		}
		clean_pipes(&prev_pipe, current, &fd);
		current = current->next;
	}
	await_process(pid, table);
	restore_fd(&fd);
	return (0);
}
