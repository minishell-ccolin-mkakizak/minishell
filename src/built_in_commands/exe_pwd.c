/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:10:59 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/11 14:24:01 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exe_pwd(t_command *cmd, t_cmnd_tbl *table, t_fd *fd)
{
	char	*dir;

	(void)cmd;
	(void)table;
	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		restore_fd(fd);
		printf("minishell: pwd: %s\n", strerror(errno));
		return ;
	}
	printf("%s\n", dir);
}
