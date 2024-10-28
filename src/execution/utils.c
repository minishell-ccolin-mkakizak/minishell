/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:45:11 by minoka            #+#    #+#             */
/*   Updated: 2024/10/28 10:45:29 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	throw_error(char *message, int exit_status, int error_number)
{
	if (error_number)
		errno = error_number;
	perror(message);
	exit(exit_status);
}

pid_t	safe_fork(void)
{
	pid_t	res;

	res = fork();
	if (res == -1)
		throw_error("bash: creating child process failed", EXIT_FAILURE, EINTR);
	return (res);
}