/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:53:08 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/09 14:55:41 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

// void    handle_input_files(t_command *cmd)
// {
// 	int i;
// 	int fd;
// 	int flags;

// 	i = 0;
// 	while(cmd->input_file[i])
// 	{
// 		flags = O_RDONLY;

// 		fd = open(cmd->input_file[i], flags, 0644);
// 		if(fd == -1)
// 		{
// 			ft_printf("minishell: %s: %s\n", cmd->input_file, strerror(errno));
// 			exit(EXIT_FAILURE);
// 		}
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 		i++;
// 	}
// }

// int input_redirect(t_command *cmd)
// {
// 	int fd;
// 	int flags;

// 	// if(cmd->heredoc_delimiter)
// 	// {
// 	// 	handle_heredoc(cmd);
// 	// 	return(0);
// 	// }
	
// 	handle_input_files(cmd);


// 	return (0);
// }