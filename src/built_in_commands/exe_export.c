/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:14:22 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/20 17:05:37 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_export(t_command *cmd, t_cmnd_tbl *table)
{
	puts("YOU MADE IT TO EXPORT");

	t_env_list	*current;
	t_env_list	*prev;
	t_env_list	*temp;

	char 		*env;

	if (!table->envp  || !cmd->args[1])
	{
		//error handling if no env
		return ;
	}
	current = table->envp;
	env = cmd->args[1];
	prev = NULL;
	if (current && is_match(current->name, env))
	{
		table->envp = current->next;
		return (free_env_node(current));
	}
	while (current && !is_match(current->name, env))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = create_node(env);
		prev->next->next = current->next;
		return (free_env_node(current));
	}
	else
	{
		prev->next = create_node(env);
	}
	return ;
}