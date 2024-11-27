/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:32:20 by minoka            #+#    #+#             */
/*   Updated: 2024/11/27 15:33:16 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

void	free_command_table(t_cmnd_tbl *table)
{
	if(table == NULL)
		return ;
	if(table->envp)
		free_env_list(table->envp);
	// if(table->head)
	// 	free(table->head);
	free(table);
}