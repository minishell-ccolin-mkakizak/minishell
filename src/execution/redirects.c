/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:44:07 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 14:10:18 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int redirects(t_command *current, t_fd *fd, int prev_pipe)
{
	setup_pipes(&prev_pipe, current, fd);
	if(current->last_input_heredoc == HEREDOC)
	{
		input_redirect(current, fd);
		heredoc_redirect(current, fd);
	}
	else
	{
		heredoc_redirect(current, fd);
		input_redirect(current, fd);
	}
	if(current->last_output_append == APPEND)
	{
		output_redirect(current, fd);
		append_redirect(current, fd);
	}
	else
	{
		output_redirect(current, fd);
		append_redirect(current, fd);
	}
	return (0);
}

int output_redirect(t_command *cmd, t_fd *fd)
{
	int file_fd;
	int flags;
	int i;

	if(cmd->output_file == NULL || cmd->output_file[0] == NULL)
		return(0);


	i = 0;
	while(cmd->output_file[i])
	{
		flags = O_WRONLY | O_CREAT ;

		file_fd = open(cmd->output_file[i], flags, 0644);
		if(file_fd == -1)
		{	
			restore_fd(fd);
			ft_printf("minishell: %s: %s\n", cmd->output_file[i], strerror(errno));
			exit(EXIT_FAILURE);
		}
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
		i++;
	}
	return (0);
}

int append_redirect(t_command *cmd, t_fd *fd)
{
	int file_fd;
	int flags;
	int i;

	if(cmd->append == NULL || cmd->append[0] == NULL)
		return(0);

	i = 0;
	while(cmd->append[i])
	{
		//append is >> 
		flags = O_WRONLY | O_CREAT | O_APPEND;

		file_fd = open(cmd->append[i], flags, 0644);
		if(file_fd == -1)
		{
			restore_fd(fd);
			ft_printf("minishell: %s: %s\n", cmd->append[i], strerror(errno));
			exit(EXIT_FAILURE);
		}
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
		i++;
	}
	return (0);
}


int input_redirect(t_command *cmd, t_fd *fd)
{
	int file_fd;
	int flags;
	int i;

	if(cmd->input_file == NULL || cmd->input_file[0] == NULL)
		return(0);

	i = 0;
	while(cmd->input_file[i])
	{
		flags = O_RDONLY;

		file_fd = open(cmd->input_file[i], flags, 0644);
		if(file_fd == -1)
		{
			restore_fd(fd);
			ft_printf("minishell: %s: %s\n", cmd->input_file[i], strerror(errno));
			exit(EXIT_FAILURE);
		}
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
		i++;
	}
	return (0);
}