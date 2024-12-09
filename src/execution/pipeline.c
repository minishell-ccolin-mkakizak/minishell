/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:02 by minoka            #+#    #+#             */
/*   Updated: 2024/12/09 16:07:46 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// typedef struct s_command
// {
// 	char				*command;
// 	char				**args;
// 	char				*input_file;
// 	char				** ;
// 	char				*heredoc_delimiter;
// 	char				**append;
// 	int					pipe_in;
// 	int					pipe_out;
// 	int					is_built_in;
// 	struct s_command	*next;
// }						t_command;

//TODO: i need a way to know which is the last redirection in the list 
	// like if i have echo hello > file1 >> file2 > file3
	//then hello should be written in the file3

int output_redirect(t_command *cmd)
{
	int fd;
	int flags;
	int i;

	if(cmd->output_file == NULL || cmd->output_file[0] == NULL)
		return(0);


	i = 0;
	while(cmd->output_file[i])
	{
		//output file is >
		flags = O_WRONLY | O_CREAT ;

		fd = open(cmd->output_file[i], flags, 0644);
		if(fd == -1)
		{	
			ft_printf("minishell: %s: %s\n", cmd->output_file[i], strerror(errno));
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

int append_redirect(t_command *cmd)
{
	int fd;
	int flags;
	int i;

	if(cmd->append == NULL || cmd->append[0] == NULL)
		return(0);

	i = 0;
	while(cmd->append[i])
	{
		//append is >> 
		flags = O_WRONLY | O_CREAT | O_APPEND;

		fd = open(cmd->append[i], flags, 0644);
		if(fd == -1)
		{
			ft_printf("minishell: %s: %s\n", cmd->append[i], strerror(errno));
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
	return (0);
}


int input_redirect(t_command *cmd)
{
	int fd;
	int flags;
	int i;

	if(cmd->input_file == NULL || cmd->input_file[0] == NULL)
		return(0);

	i = 0;
	while(cmd->input_file[i])
	{
		flags = O_RDONLY;

		fd = open(cmd->input_file[i], flags, 0644);
		if(fd == -1)
		{
			ft_printf("minishell: %s: %s\n", cmd->input_file[i], strerror(errno));
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
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

void await_process(pid_t pid, t_cmnd_tbl *table)
{
	pid_t wpid;
	int status;

	wpid = -1;
	while (1)
	{
		wpid = wait(&status);

		if(wpid < 0)
		{
			// need to implement error handing
			break;
		}
		if(pid == wpid)
		{
			table->last_exit_status = WEXITSTATUS(status);
		}
	}
	return ;
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
	is_child = FALSE;
	pid = -1;
	init_fd(&fd);



	while(current)
	{

		if(current->next)
			init_pipe(&fd);

		if(current->next || !current->is_built_in || has_pipe(table->head))
		{
			pid = safe_fork();
			
		}
		if(pid == 0)
		{	
			is_child = TRUE;
			setup_pipes(&prev_pipe, current, &fd);
			input_redirect(current);
			heredoc_redirect(current);
			output_redirect(current);
			append_redirect(current);
			if(current->is_built_in)
				built_in_cmds(current, table, is_child);
			else
				execute_cmd(current, table, is_child, envp);
		}
		else if (current->is_built_in && !has_pipe(table->head))
		{

			built_in_cmds(current, table, is_child);
		}

		clean_pipes(&prev_pipe, current, &fd);
		current = current->next;
	}

	await_process(pid, table);
	// puts("end of piepline\n");
	// free_command_list(table->head);
	// printf("exit status is : %d\n", table->last_exit_status);
	restore_fd(&fd);
	return (0);
}

