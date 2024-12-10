/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:14:22 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 15:29:05 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_env_node(t_env_list **envp, char **str_array)
{
	t_env_list	*new_node;

	new_node = create_node(str_array[0], str_array[1]);
	new_node->next = *envp;
	*envp = new_node;
}

void	find_and_update_env(t_env_list **envp, char *env)
{
	t_env_list	*current;
	t_env_list	*prev;
	char		**str_array;

	current = *envp;
	prev = NULL;
	str_array = ft_split(env, '=');
	while (current && !is_match(current->name, env))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		if (prev)
			prev->next = current->next;
		else
			*envp = current->next;
		free_env_node(current);
	}
	add_env_node(envp, str_array);
}

void	exe_export(t_command *cmd, t_cmnd_tbl *table)
{
	if (!table->envp || !cmd->args || !cmd->args[0])
		return ;
	find_and_update_env(&table->envp, cmd->args[0]);
}
