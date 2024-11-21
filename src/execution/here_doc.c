/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:54:32 by minoka            #+#    #+#             */
/*   Updated: 2024/11/21 16:47:03 by mkakizak         ###   ########.fr       */
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
