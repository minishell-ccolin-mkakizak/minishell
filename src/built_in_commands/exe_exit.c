/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:15:13 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/11 14:24:01 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exe_exit(t_command *cmd, t_cmnd_tbl *table)
{
	(void)cmd;
	(void)table;
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
