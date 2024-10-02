/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:46:10 by mkakizak          #+#    #+#             */
/*   Updated: 2024/09/23 18:44:37 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sort_two(t_c_list **head, char stack)
{
	if ((stack == 'b') && is_smaller((*head)->content, (*head)->next->content))
		ft_lstswap(head, stack);
	if (stack == 'a' && is_smaller((*head)->next->content, (*head)->content))
		ft_lstswap(head, stack);
	return (TRUE);
}

int	sort_three(t_c_list **head, int target_nbr, char stack)
{
	int	target_index;
	int	is_sorted;

	is_sorted = check_either_sort(*head, stack);
	if (!is_sorted)
		ft_lstswap(head, stack);
	if (is_smaller(find_nbr(*head, target_nbr), find_r_nbr(*head, target_nbr)))
		target_index = find_nbr(*head, target_nbr);
	else
		target_index = find_r_nbr(*head, target_nbr) * -1;
	while (target_index != 0)
	{
		if (target_index > 0)
		{
			ft_rotate(head, stack);
			target_index--;
		}
		else
		{
			ft_r_rotate(head, stack);
			target_index++;
		}
	}
	return (TRUE);
}

int	sort_two_three(t_c_list **head, int len, char stack)
{
	int	smallest;
	int	largest;

	smallest = find_min(*head);
	largest = find_max(*head);
	if (len == 2)
	{
		sort_two(head, stack);
	}
	if (len == 3)
	{
		if (stack == 'a')
		{
			sort_three(head, smallest, stack);
		}
		if (stack == 'b')
		{
			sort_three(head, largest, stack);
		}
	}
	return (TRUE);
}

int	sort_six(t_c_list **stack_a, t_c_list **stack_b)
{
	split_lsts_tw_thr(stack_a, stack_b);
	sort_two_three(stack_a, ft_c_lstsize(*stack_a), 'a');
	sort_two_three(stack_b, ft_c_lstsize(*stack_b), 'b');
	push_all(stack_b, stack_a, 'a');
	return (TRUE);
}

int	sort_short(t_c_list **stack_a, t_c_list **stack_b, int len)
{
	int	index;

	if (check_any_sort(*stack_a))
	{
		index = find_sortest_path(stack_a, 1);
		rotate_stack(stack_a, 'a', index);
		ft_c_lstclear(stack_a);
		return (TRUE);
	}
	if (len <= 3)
	{
		sort_two_three(stack_a, len, 'a');
		return (TRUE);
	}
	if (len <= 6)
	{
		sort_six(stack_a, stack_b);
		return (TRUE);
	}
	return (FALSE);
}
