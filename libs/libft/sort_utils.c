/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:58:06 by mkakizak          #+#    #+#             */
/*   Updated: 2024/09/23 18:44:43 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_sort(t_c_list *head)
{
	int			i;
	t_c_list	*current;

	i = find_min(head);
	current = head;
	while (1)
	{
		if (current->content == i)
		{
			current = current->next;
			i++;
		}
		else
		{
			return (FALSE);
		}
		if (current == head)
			return (TRUE);
	}
	return (FALSE);
}

int	check_r_sort(t_c_list *head)
{
	int			i;
	t_c_list	*current;

	i = ft_c_lstsize(head);
	current = head;
	while (1)
	{
		if (current->content == i)
		{
			i--;
			current = current->next;
		}
		else
		{
			return (FALSE);
		}
		if (current == head)
			return (TRUE);
	}
	return (FALSE);
}

int	find_nbr(t_c_list *head, int nbr)
{
	int			i;
	t_c_list	*current;

	if (head == NULL || nbr == 0)
		return (FALSE);
	i = 0;
	current = head;
	while (1)
	{
		if (current->content != nbr)
		{
			i++;
			current = current->next;
		}
		else
		{
			return (i);
		}
		if (current == head)
			return (FALSE);
	}
	return (FALSE);
}

int	find_r_nbr(t_c_list *head, int nbr)
{
	int			i;
	t_c_list	*current;

	if (head == NULL || nbr == 0)
		return (FALSE);
	i = 0;
	current = head;
	while (1)
	{
		if (current->content != nbr)
		{
			i++;
			current = current->prev;
		}
		else
		{
			return (i);
		}
		if (current == head)
			return (FALSE);
	}
	return (FALSE);
}

int	check_any_sort(t_c_list *head)
{
	int	size;
	int	i;

	i = 0;
	size = ft_c_lstsize(head);
	while (i < size)
	{
		if (check_sort(head))
			return (TRUE);
		head = head->next;
		i++;
	}
	if (check_sort(head))
		return (TRUE);
	else
		return (FALSE);
}
