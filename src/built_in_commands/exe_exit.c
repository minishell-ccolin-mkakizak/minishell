/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:15:13 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/26 15:50:06 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_exit(t_command *cmd, t_cmnd_tbl *table)
{
	ft_printf("exit\n");
	exit(EXIT_SUCCESS);
}
