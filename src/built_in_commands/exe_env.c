/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:11:56 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 13:16:16 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_env(t_command *cmd, t_cmnd_tbl *table)
{
	if(table->envp == NULL)
		ft_printf("enpv is NULL\n");
	else
		print_env_list(table->envp);
}
