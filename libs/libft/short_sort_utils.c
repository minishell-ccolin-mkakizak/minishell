/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:30:24 by mkakizak          #+#    #+#             */
/*   Updated: 2024/09/23 18:44:33 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	split_lsts_tw_thr(t_c_list **stack_a, t_c_list **stack_b)
{
	int	i;
	int	index;
	int	half;

	i = 0;
	index = 0;
	half = ft_c_lstsize(*stack_a) / 2;
	while (i++ < half)
	{
		index = recon_smaller(*stack_a, half);
		while (index != 0)
		{
			if (index > 0)
			{
				ft_rotate(stack_a, 'a');
				index--;
			}
			else
			{
				ft_r_rotate(stack_a, 'a');
				index++;
			}
		}
		ft_c_push(stack_a, stack_b, 'b');
	}
}

int	check_either_sort(t_c_list *head, char stack)
{
	if (stack == 'a')
		return (check_any_sort(head));
	else
		return (check_any_r_sort(head));
}

void	ft_c_print_lst(t_c_list *head, char stack)
{
	t_c_list	*current;
	int			i;

	current = head;
	if (head == NULL)
	{
		ft_printf("List [%c]is NULL\n", stack);
		return ;
	}
	i = 0;
	while (1)
	{
		if (i == 0)
		{
			ft_printf("[%d]:%d<-head[%c]\n", i, current->content, stack);
		}
		else
		{
			ft_printf("[%d]:%d\n", i, current->content);
		}
		current = current->next;
		i++;
		if (current == head)
			break ;
	}
}
