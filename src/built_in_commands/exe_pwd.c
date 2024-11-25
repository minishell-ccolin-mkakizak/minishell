/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:10:59 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/20 15:19:52 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_pwd(t_command *cmd, t_cmnd_tbl *table)
{
	char *dir;

	dir = getcwd(NULL, 0);
	ft_printf("%s\n", dir);
}
