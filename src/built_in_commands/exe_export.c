/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:14:22 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/28 14:20:43 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_export(t_command *cmd, t_cmnd_tbl *table)
{
	puts("YOU MADE IT TO EXPORT");

	t_env_list	*current;
	t_env_list	*prev;
	t_env_list	*temp;
	char 		**str_array;
	char 		*env;

	if (!table->envp  || !cmd->args[0])
	{
		return ;
	}
	current = table->envp;
	env = cmd->args[0];
	prev = NULL;
	str_array = ft_split(env, '=');
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
		prev->next = create_node(str_array[0], str_array[1]);
		prev->next->next = current->next;
		return (free_env_node(current));
	}
	else
	{
		prev->next = create_node(str_array[0], str_array[1]);
	}
	return ;
}
