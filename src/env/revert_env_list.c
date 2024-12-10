/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revert_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:36:19 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 15:24:13 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_list_len(t_env_list *head)
{
	t_env_list	*current;
	int			count;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**revert_envp_list(t_env_list *head)
{
	t_env_list	*current;
	int			count;
	char		**envp;
	int			i;
	char		*temp;

	count = get_list_len(head);
	envp = ft_calloc(sizeof(char *), count + 1);
	if (envp == NULL)
		return (NULL);
	current = head;
	i = 0;
	while (current)
	{
		temp = ft_strjoin(current->name, "=");
		envp[i] = ft_strjoin(temp, current->value);
		free(temp);
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	free_env_list(head);
	return (envp);
}
