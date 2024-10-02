/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:27:04 by mkakizak          #+#    #+#             */
/*   Updated: 2024/09/17 18:12:02 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_arr(int *arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_printf("[%d]:%s\n", i, arr[i]);
		i++;
	}
	return (0);
}

void	error(void)
{
	write(2, "Error\n", 6);
	exit (1);
}

void	check_doubles(int *args_array, long nbr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (nbr == args_array[i] && nbr != 0)
		{
			free(args_array);
			error();
		}
		i++;
	}
}

int	*args_validation(int argc, char *argv[])
{
	int		i;
	int		*args_array;
	long	nbr;
	long	was_zero;

	was_zero = 0;
	args_array = ft_calloc(sizeof(long), argc);
	if (args_array == NULL)
		error();
	i = 1;
	while (i < argc)
	{
		nbr = ft_atoi_long(argv[i]);
		if ((nbr > INT_MAX || nbr < INT_MIN))
			error();
		check_doubles(args_array, nbr, i);
		if (was_zero && nbr == 0)
			error();
		if (nbr == 0 && !was_zero)
				was_zero = 1;
		args_array[i - 1] = nbr;
		i++;
	}
	return (args_array);
}
