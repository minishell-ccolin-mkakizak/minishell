/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:02 by minoka            #+#    #+#             */
/*   Updated: 2024/10/30 13:43:22 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int check_for_dilimiter(t_command *cmd, char *input)
{
	int len;

	len = ft_strlen(input);

	input[len -1] = '\0';

	if(ft_strncmp(input, cmd->heredoc_delimiter, len) == 0)
		return (TRUE);

	return (FALSE);
}

int handle_heredoc(t_command *cmd)
{
	char 	*input;
	int		pipe_fd[2];
	size_t	len;

	if(pipe(pipe_fd) == -1)
	{
		/// need to implement error handling here

		return (-1);
	}

	// will loop until heredoc_dilimiter is met
	while(1)
	{
		ft_printf("->");
		input = get_next_line(STDIN_FILENO);
		if(input ==  NULL)
		{
			//need to handle error handing here
			break;
		}
		len = ft_strlen(input);
		if(check_for_dilimiter(cmd, input))
		{
			free(input);
			break;
		}
		input[len -1] = '\n';
		write(pipe_fd[1], input, len);
		free(input);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}

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

int execute_pipeline(t_cmnd_tbl *table, char *envp[])
{
	//maybe i can add some of these to the table struct
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
			setup_pipes(&prev_pipe, current, &fd);
			input_redirect(current);
			output_redirect(current);
			execute_cmd(current, envp);
		}
		clean_pipes(&prev_pipe, current, &fd);
		current = current->next;
	}

	while (wait(&status) > 0);
	restore_fd(&fd);
	return (0);
}
