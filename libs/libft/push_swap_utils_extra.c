/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:00:59 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/11 14:20:34 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rotate(t_c_list **head, char stack)
{
	*head = (*head)->next;
	ft_printf("r%c\n", stack);
}

void	ft_r_rotate(t_c_list **head, char stack)
{
	*head = (*head)->prev;
	ft_printf("rr%c\n", stack);
}

void	rotate_stack(t_c_list **src, int stack, int index)
{
	if (!src || !*src)
		return ;
	while (index != 0)
	{
		if (index > 0)
		{
			ft_rotate(src, stack);
			index--;
		}
		else
		{
			ft_r_rotate(src, stack);
			index++;
		}
	}
}

void	ft_lstswap(t_c_list **head, char stack)
{
	int	temp;

	temp = (*head)->content;
	(*head)->content = (*head)->next->content;
	(*head)->next->content = temp;
	ft_printf("s%c\n", stack);
}

void	ft_c_lstclear(t_c_list **head)
{
	t_c_list	*current;
	t_c_list	*next;

	current = (*head)->next;
	if (*head == NULL)
		return ;
	while (current != *head)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(*head);
	*head = NULL;
}
