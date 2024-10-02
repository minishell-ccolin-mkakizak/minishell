/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:04:38 by mkakizak          #+#    #+#             */
/*   Updated: 2024/09/23 18:44:46 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	split_lsts_ch(t_c_list **src, t_c_list **dest, int dlmt, int chunk_size)
{
	int		i;
	int		index;
	char	src_stack;

	i = 0;
	index = 0;
	src_stack = 'a';
	while (i++ <= chunk_size)
	{
		if (src_stack == 'a')
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
		ft_c_push(src, dest, 'b');
	}
}

void	chunk_and_push(t_c_list **src, t_c_list **dest, int len)
{
	int	dlmt;
	int	bias;
	int	chunk_size;

	bias = 14;
	chunk_size = len / bias;
	if (chunk_size == 0)
		chunk_size = 5;
	dlmt = chunk_size;
	while (*src != NULL)
	{
		split_lsts_ch(src, dest, dlmt, chunk_size);
		if (dlmt >= len)
			break ;
		dlmt += chunk_size;
		if (dlmt > len)
			dlmt = len;
	}
}

void	sort_back(t_c_list **stack_a, t_c_list **stack_b)
{
	int	i;
	int	target_nbr;
	int	index;
	int	size;

	i = 0;
	target_nbr = find_max(*stack_b);
	size = ft_c_lstsize(*stack_b);
	while (i < size)
	{
		index = find_sortest_path(stack_b, target_nbr);
		rotate_stack(stack_b, 'b', index);
		ft_c_push(stack_b, stack_a, 'a');
		target_nbr--;
		i++;
	}
}

int	long_sort(t_c_list **stack_a, t_c_list **stack_b, int len)
{
	int	dlmt;

	dlmt = ft_c_lstsize(*stack_a) / 2;
	splt_lst_hlf(stack_a, stack_b, 'b', dlmt);
	while (1)
	{
		dlmt /= 2;
		splt_lst_hlf(stack_b, stack_a, 'a', dlmt);
		if (dlmt <= 3)
			break ;
	}
	chunk_and_push(stack_a, stack_b, len);
	sort_back(stack_a, stack_b);
	return (TRUE);
}

void	sort(t_c_list **head, int len)
{
	t_c_list	*stack_a;
	t_c_list	*stack_b;
	int			index;

	stack_a = *head;
	stack_b = NULL;
	if (check_any_sort(stack_a))
	{
		index = find_sortest_path(&stack_a, 1);
		rotate_stack(&stack_a, 'a', index);
		ft_c_lstclear(&stack_a);
		return ;
	}
	if (ft_c_lstsize(stack_a) <= 6)
		sort_short(&stack_a, &stack_b, len);
	else
		long_sort(&stack_a, &stack_b, len);
	ft_c_lstclear(&stack_a);
}
