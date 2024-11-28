/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:57:28 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/28 14:49:09 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// function to print all envp
void print_env_list(t_env_list *head)
{
	t_env_list *current = head;
	int count = 0;
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

t_env_list *create_node(char *name, char *value)
{
	t_env_list *node;
	char	**str_array;

	node = ft_calloc(sizeof(t_env_list), 1);
	if(node == NULL)
		return (NULL);
	// str_array = ft_split(env, '=');
	// ft_printf("env:%s=%s\n", str_array[0], str_array[1]);

	node->name = ft_strdup(name);
	if(node->name == NULL)
		return (NULL);

	if(value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;

	// ft_free_all(str_array);
	return (node);
}

t_env_list *init_env(char *envp[])
{
	t_env_list	*head;
	t_env_list	*current;
	t_env_list	*new_node;
	char		**str_array;
	int 		i;
	i = 1;

	if(envp == NULL || envp[0] == NULL)
		return(NULL);

	// make the head
	str_array = ft_split(envp[0], '=');
	head = create_node(str_array[0], str_array[1]);
	if(head == NULL)
		return (NULL);
	ft_free_all(str_array);
	current = head;
	while(envp[i])
	{
		// need to iterate on each envp and add to the linked list;
		str_array = ft_split(envp[i], '=');
		new_node = create_node(str_array[0], str_array[1]);
		ft_free_all(str_array);
		if(new_node == NULL)
			return (NULL);
		current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
