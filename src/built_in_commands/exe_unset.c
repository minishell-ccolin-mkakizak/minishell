/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:20:31 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/14 13:52:10 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_unset(t_command *cmd, t_env_list *env)
{
	t_env_list	*current;
	t_env_list	*prev;

	char *name;

	puts("YOU MADE IT TO UNSET");

	if (!env  || !cmd->args[1])
	{
		//error handling if no name
		return ;
	}

	current = env;
	name = cmd->args[1];
	prev = NULL;
	if (current && strcmp(current->name, name) == 0)
	{
		env = current->next;
		return (free_env_node(current));
	}
	while (current && strcmp(current->name, name) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;

	// Unlink the node
	prev->next = current->next;
	return (free_env_node(current));
}

