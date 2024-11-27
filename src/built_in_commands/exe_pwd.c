/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:10:59 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/27 15:26:48 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_pwd(t_command *cmd, t_cmnd_tbl *table)
{
	char *dir;

	dir = getcwd(NULL, 0);
	if(dir == NULL)
	{
		ft_printf("minishell: pwd: %s\n", strerror(errno));
		return ;
	}
	ft_printf("%s\n", dir);
}
