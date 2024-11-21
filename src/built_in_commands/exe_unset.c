/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:20:31 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/21 15:56:48 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_unset(t_command *cmd, t_cmnd_tbl *table)
{
	t_env_list	*current;
	t_env_list	*prev;

	char 		*name;

	puts("YOU MADE IT TO UNSET");

	if (!table->envp  || !cmd->args[0])
	{
		//error handling if no name
		return ;
	}
	current = table->envp;
	name = cmd->args[0];
	prev = NULL;
	if (current && is_match(current->name, name))
	{
		table->envp = current->next;
		return (free_env_node(current));
	}
	while (current && !is_match(current->name, name))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		return (free_env_node(current));
	}
	return ;
}

