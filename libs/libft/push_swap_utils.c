/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:23:36 by mkakizak          #+#    #+#             */
/*   Updated: 2024/09/23 18:44:26 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_c_list	*ft_c_lstnew(int content)
{
	t_c_list	*node;

	node = (t_c_list *)ft_calloc(sizeof(t_c_list), 1);
	if (node == NULL)
	{
		error();
	}
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_c_push(t_c_list **src, t_c_list **dest, char stack)
{
	ft_c_lstadd(dest, ft_lstpop(src));
	ft_printf("p%c\n", stack);
}

void	ft_c_lstadd(t_c_list **head, t_c_list *new)
{
	t_c_list	*last;

	if (!new)
		return ;
	if (!*head)
	{
		new->next = new;
		new->prev = new;
		*head = new;
	}
	last = (*head)->prev;
	new->next = *head;
	new->prev = last;
	(*head)->prev = new;
	last->next = new;
	*head = new;
}

t_c_list	*ft_lstpop(t_c_list **head)
{
	t_c_list	*popped;

	if (!head || !*head)
		return (NULL);
	popped = *head;
	if (popped->next == popped)
	{
		*head = NULL;
	}
	else
	{
		popped->prev->next = popped->next;
		popped->next->prev = popped->prev;
		*head = popped->next;
	}
	popped->next = popped;
	popped->prev = popped;
	return (popped);
}

int	ft_c_lstsize(t_c_list *lst)
{
	int			res;
	t_c_list	*current;

	if (!lst)
		return (0);
	current = lst;
	res = 1;
	while (1)
	{
		lst = lst->next;
		if (lst == current)
			return (res);
		res++;
	}
	return (res);
}
