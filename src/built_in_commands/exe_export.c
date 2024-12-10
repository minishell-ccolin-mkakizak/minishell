/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:14:22 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 16:42:04 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_no_args(t_env_list *head)
{
	t_env_list	*current;

	current = head;
	while (current)
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
	int	result;

	if (!str || *str == '\0')
		return (0);
	result = 1;
	i = 0;
	while (str[i])
	{
		if (i == 0)
			result = is_valid_key_char(str[i], 1);
		else
			result = is_valid_key_char(str[i], 0);
		if (result == 0)
			return (0);
		i++;
	}
	return (1);
}

void	print_export_error(char *arg, t_fd *fd)
{
	restore_fd(fd);
	ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
}

void	find_and_replace_env(t_cmnd_tbl *table, char **str_array)
{
	t_env_list	*current;
	t_env_list	*prev;
	t_env_list	*new_node;

	current = table->envp;
	prev = NULL;
	while (current && !is_match(current->name, str_array[0]))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		if (prev)
			prev->next = create_node(str_array[0], str_array[1]);
		else
			table->envp = create_node(str_array[0], str_array[1]);
		free_env_node(current);
	}
	else if (prev)
		prev->next = create_node(str_array[0], str_array[1]);
	else
		table->envp = create_node(str_array[0], str_array[1]);
}

void	exe_export(t_command *cmd, t_cmnd_tbl *table, t_fd *fd)
{
	char	**str_array;

	if (!table->envp)
		return ;
	if (!cmd->args)
	{
		print_no_args(table->envp);
		return ;
	}
	if (!is_valid_identifier(cmd->args[0]))
	{
		print_export_error(cmd->args[0], fd);
		return ;
	}
	str_array = ft_split(cmd->args[0], '=');
	if (!str_array)
		return ;
	find_and_replace_env(table, str_array);
}
