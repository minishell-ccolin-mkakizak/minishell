/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:19:44 by mkakizak          #+#    #+#             */
/*   Updated: 2024/09/23 18:44:40 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_any_r_sort(t_c_list *head)
{
	int	size;
	int	i;

	i = 0;
	size = ft_c_lstsize(head);
	while (i < size)
	{
		if (check_r_sort(head))
			return (TRUE);
		head = head->prev;
		i++;
	}
	if (check_r_sort(head))
		return (TRUE);
	else
		return (FALSE);
}

int	find_min(t_c_list *head)
{
	t_c_list	*current;
	int			res;

	current = head;
	res = INT_MAX;
	while (1)
	{
		if (res > current->content && (current->content > 0))
			res = current->content;
		current = current->next;
		if (current == head)
		{
			return (res);
		}
	}
	return (0);
}

int	find_max(t_c_list *head)
{
	t_c_list	*current;
	int			res;

	current = head;
	res = INT_MIN;
	while (1)
	{
		if (res < current->content)
			res = current->content;
		current = current->next;
		if (current == head)
		{
			return (res);
		}
	}
	return (0);
}

int	find_sortest_path(t_c_list **src, int target_nbr)
{
	int	res;

	res = 0;
	if (is_smaller(find_nbr(*src, target_nbr), find_r_nbr(*src, target_nbr)))
		res = find_nbr(*src, target_nbr);
	else
		res = find_r_nbr(*src, target_nbr) * -1;
	return (res);
}

char	get_other_stack(char c)
{
	if (c == 'a')
		return ('b');
	else
		return ('a');
	return (' ');
}
