/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:10:59 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 15:23:51 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exe_pwd(t_command *cmd, t_cmnd_tbl *table, t_fd *fd)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		restore_fd(fd);
		ft_printf("minishell: pwd: %s\n", strerror(errno));
		return ;
	}
	ft_printf("%s\n", dir);
}
