/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_sort_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:25:28 by mkakizak          #+#    #+#             */
/*   Updated: 2024/07/05 13:50:24 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	splt_lst_hlf(t_c_list **src, t_c_list **dest, char stk, int dlmt)
{
	int		i;
	int		index;
	int		len;
	char	src_stack;

	i = 0;
	index = 0;
	len = (ft_c_lstsize(*src) / 2);
	src_stack = get_other_stack(stk);
	while (i++ <= len)
	{
		if (stk == 'b')
		{
			index = recon_smaller(*src, dlmt);
			if (index == INT_MAX)
			{
				i++;
				break ;
			}
		}
		else
			index = recon_larger(*src, dlmt);
		rotate_stack(src, src_stack, index);
		ft_c_push(src, dest, stk);
	}
}

void	push_all(t_c_list **src_lst, t_c_list **dest_lst, char dest_stack)
{
	int	i;
	int	size;

	size = ft_c_lstsize(*src_lst);
	i = 0;
	while (i < size)
	{
		ft_c_push(src_lst, dest_lst, dest_stack);
		i++;
	}
	*src_lst = NULL;
}

int	recon_smaller(t_c_list *head, int deli)
{
	int			i;
	int			index;
	int			r_index;
	t_c_list	*temp;
	t_c_list	*r_temp;

	i = 0;
	index = 0;
	r_index = 0;
	temp = head;
	r_temp = head;
	while (i < ft_c_lstsize(head))
	{
		if (temp->content <= deli)
			return (index);
		temp = temp->next;
		index++;
		if (r_temp->content <= deli)
			return (r_index);
		r_temp = r_temp->prev;
		r_index--;
		i++;
	}
	return (INT_MAX);
}

int	recon_larger(t_c_list *head, int deli)
{
	int			i;
	int			index;
	int			r_index;
	t_c_list	*temp;
	t_c_list	*r_temp;

	i = 0;
	index = 0;
	r_index = 0;
	temp = head;
	r_temp = head;
	while (i < ft_c_lstsize(head))
	{
		if (temp->content > deli)
			return (index);
		temp = temp->next;
		index++;
		if (r_temp->content > deli)
			return (r_index);
		r_temp = r_temp->prev;
		r_index--;
		i++;
	}
	return (0);
}
