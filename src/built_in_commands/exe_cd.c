/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:09:16 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/22 16:19:03 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_cd(t_command *cmd, t_cmnd_tbl *table)
{
	// this need error handeling for more then 1 args
	// need go to home if '~'
	if(cmd->args == NULL || cmd->args[0] == NULL)
	{
		chdir(getenv("HOME"));
		return ;
	}
	chdir(cmd->args[0]);
	puts("YOU MADE IT TO CD!!");
}