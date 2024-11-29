/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:33:38 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/29 14:19:17 by mkakizak         ###   ########.fr       */
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


void free_env_list(t_env_list *head)
{
	t_env_list *current = head;
	while (current != NULL)
	{
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

void free_command_list(t_cmnd_tbl *table)
{
	t_command *current;
	t_command *temp;
	
	if(table->head == NULL)
		return ;

	current = table->head;
	
	while (current != NULL) 
	{
		temp = current;
		if(current->args != NULL) 
			ft_free_all(current->args);
		if(current->output_file != NULL) 
			ft_free_all(current->output_file);
		if(current->append != NULL) 
			ft_free_all(current->append);
		if(current->command) 
			free(current->command);
		if(current->input_file) 
			free(current->input_file);
		if(current->heredoc_delimiter) 
			free(current->heredoc_delimiter);
		current = current->next;
		if(temp)
		{
			free(temp);
			temp = NULL;
		}
	}
	table->head = NULL;
}


void free_command_table(t_cmnd_tbl *table)
{
	if (!table)
		return;
	if(table->head)
	{
		puts("does it think there is a head?");
		free_command_list(table);
	}
	if(table->envp)
	{
		free_env_list(table->envp);
	}	
	free(table);
}