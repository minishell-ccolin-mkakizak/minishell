/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:33:38 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/28 15:08:10 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


// typedef struct s_command
// {
// 	char				*command;
// 	char				**args;
// 	char				*input_file;
// 	char				**output_file;
// 	char				*heredoc_delimiter;
// 	char				**append;
// 	int					pipe_in;
// 	int					pipe_out;
// 	int					is_built_in;
// 	struct s_command	*next;
// }						t_command;


void free_command_list(t_command *head)
{
	if(head == NULL)
		return ;
	t_command *current = head;
	while (current != NULL) 
	{
		t_command *temp = current;
		if(temp->args != NULL && temp->args[0] != NULL)
			ft_free_all(temp->args);
		if(temp->output_file != NULL && temp->output_file[0] != NULL)
			ft_free_all(temp->output_file);
		if(temp->append != NULL && temp->append[0] != NULL)
			ft_free_all(temp->append);
		if(temp->command)
			free(temp->command);
		if(temp->input_file)
			free(temp->input_file);
		if(temp->heredoc_delimiter)
			free(temp->heredoc_delimiter);
		current = current->next;
		if(temp)
			free(temp);
	}
}

void free_env_list(t_env_list *head)
{
	t_env_list *current = head;
	while (current != NULL) {
		t_env_list *temp = current;
		current = current->next;
		free_env_node(temp);
	}
}

void free_env_node(t_env_list *node)
{
	if(node == NULL)
		return ;
	if(node->name)
		free(node->name);
	if(node->value)
		free(node->value);
	free(node);
}

void free_command_table(t_cmnd_tbl *table)
{
	if (!table)
	return;
	free_command_list(table->head);
	free_env_list(table->envp);
	free(table);
}