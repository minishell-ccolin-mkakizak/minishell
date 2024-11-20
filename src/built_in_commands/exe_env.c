/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:11:56 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/20 15:19:39 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_env(t_command *cmd, t_cmnd_tbl *table)
{
	// need to add some error checking also formattig is not quit right
	print_env_list(table->envp);
	puts("YOU MADE IT TO ENV");
}