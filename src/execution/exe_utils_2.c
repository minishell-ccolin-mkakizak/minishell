/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:44:18 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/13 13:53:28 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_unnecessary_fds(t_fd *fd)
{
	if (fd->stdin_backup != STDIN_FILENO)
		close(fd->stdin_backup);
	if (fd->stdout_backup != STDOUT_FILENO)
		close(fd->stdout_backup);
}
