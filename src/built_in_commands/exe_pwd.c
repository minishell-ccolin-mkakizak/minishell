/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:10:59 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/26 15:52:09 by mkakizak         ###   ########.fr       */
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
