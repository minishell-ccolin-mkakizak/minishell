/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:11:56 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/11 14:24:01 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exe_env(t_command *cmd, t_cmnd_tbl *table)
{
	(void)cmd;
	if (table->envp == NULL)
		printf("minishell: env : \n");
	else
		print_env_list(table->envp);
}
