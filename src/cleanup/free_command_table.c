/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:33:38 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/30 13:04:21 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env_list(t_env_list *head)
{
	t_env_list	*current;
	t_env_list	*temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free_env_node(temp);
	}
}

void	free_env_node(t_env_list *node)
{
	if (node == NULL)
		return ;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_command(t_command *cmd)
{
	if (cmd->args != NULL)
		ft_free_all(cmd->args);
	if (cmd->output_file != NULL)
		ft_free_all(cmd->output_file);
	if (cmd->append != NULL)
		ft_free_all(cmd->append);
	if (cmd->command)
		free(cmd->command);
	if (cmd->input_file)
		ft_free_all(cmd->input_file);
	if (cmd->heredoc_delimiter)
		ft_free_all(cmd->heredoc_delimiter);
	free(cmd);
}

void	free_command_list(t_cmnd_tbl *table)
{
	t_command	*current;
	t_command	*temp;

	if (table->head == NULL)
		return ;
	current = table->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free_command(temp);
	}
	table->head = NULL;
}

void	free_command_table(t_cmnd_tbl *table)
{
	if (!table)
		return ;
	if (table->head)
	{
		free_command_list(table);
	}
	if (table->envp)
	{
		free_env_list(table->envp);
	}
	free(table);
}
