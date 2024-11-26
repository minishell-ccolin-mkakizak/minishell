/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:11:56 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/26 15:51:12 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_env(t_command *cmd, t_cmnd_tbl *table)
{
	// need to add some error checking also formattig is not quit right
	if(table->envp == NULL)
		ft_printf("enpv is NULL\n");
	else
		print_env_list(table->envp);
	// puts("YOU MADE IT TO ENV");
}
