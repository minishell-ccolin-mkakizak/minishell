/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:14:22 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 15:31:09 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void print_no_args(t_env_list *head)
{
	t_env_list	*current;
	current = head;
	while(current)
	{
		ft_printf("declare -x ");
		ft_printf("%s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
	return ;
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	int result = 1;
	
	i = 0;
	while (str[i])
	{
		if(i == 0)
			result = is_valid_key_char(str[i], 1);
		else
			result = is_valid_key_char(str[i], 0);
		
		if(result == 0)
			return (0);
		i++;x
	}
	return (1);
}

void exe_export(t_command *cmd, t_cmnd_tbl *table, t_fd *fd)
{
	t_env_list	*current;
	t_env_list	*prev;
	t_env_list	*temp;
	char 		**str_array;
	char 		*env;

	if (!table->envp)
	{
		return ;
	}

	if(!cmd->args)
	{
		puts("here");
		print_no_args(table->envp);
		return ;
	}

	if(is_valid_identifier(cmd->args[0]) == 0)
	{
		restore_fd(fd);
		ft_printf("minishell: export: `%s': not a valid identifier\n", cmd->args[0]);
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
