/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:17:04 by mkakizak          #+#    #+#             */
/*   Updated: 2024/07/02 18:21:56 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*node;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	start = NULL;
	while (lst)
	{
		temp = f(lst->content);
		node = ft_lstnew(temp);
		if (!node)
		{
			ft_lstclear(&start, del);
			del(temp);
			return (NULL);
		}
		ft_lstadd_back(&start, node);
		lst = lst->next;
	}
	node->next = NULL;
	return (start);
}
