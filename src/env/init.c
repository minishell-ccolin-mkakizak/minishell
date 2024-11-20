/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:57:28 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/20 17:33:13 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// function to print all envp
void print_env_list(t_env_list *head)
{
	t_env_list *current = head;
	int count = 0;
	// somehow this doesn't work with ft_printf()...
	while (current != NULL) {
		ft_printf("[%d]%s=%s\n",count, current->name, current->value);
		current = current->next;
		count ++;
	}
}

char *get_env_var(t_env_list *envs, char *name)
{
	t_env_list *current;
	t_env_list *prev;

	int i;
	current = envs;

	while (current && !is_match(current->name, name))
	{
		prev = current;
		current = current->next;
	}
	if(current)
	{
		return(ft_strdup(current->value));
	}
	return(NULL);
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

t_env_list *create_node(char *env)
{
	t_env_list *node;
	char	**str_array;

	node = ft_calloc(sizeof(t_env_list), 1);
	if(node == NULL)
		return (NULL);
	str_array = ft_split(env, '=');
	// ft_printf("env:%s=%s\n", str_array[0], str_array[1]);

	node->name = ft_strdup(str_array[0]);

	if(str_array[1])
		node->value = ft_strdup(str_array[1]);
	else
		node->value = NULL;

	// if(node->name == NULL)
	// 	return (NULL);
	ft_free_all(str_array);
	return (node);
}

t_env_list *init_env(char *envp[])
{
	t_env_list	*head;
	t_env_list	*current;
	t_env_list	*new_node;
	int 		i;
	i = 1;

	if(envp == NULL || envp[0] == NULL)
		return(NULL);

	// make the head
	head = create_node(envp[0]);
	if(head == NULL)
		return (NULL);

	current = head;
	while(envp[i])
	{
		// need to iterate on each envp and add to the linked list;
		new_node = create_node(envp[i]);
		if(new_node == NULL)
			return (NULL);
		current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
