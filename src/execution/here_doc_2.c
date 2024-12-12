/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:31:53 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/12 15:01:14 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_to_pipe(char *input, int *pipe_fd)
{
	size_t	len;

	len = ft_strlen(input);
	if (len > 0)
	{
		if (input[len - 1] != '\n')
			input[len++] = '\n';
		write(pipe_fd[1], input, len);
	}
	free(input);
}
