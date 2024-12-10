/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:20:31 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 15:29:26 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exe_unset(t_command *cmd, t_cmnd_tbl *table)
{
	t_env_list	*current;
	t_env_list	*prev;
	char		*name;

	if (!table->envp || !cmd->args || !cmd->args[0])
		return ;
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
