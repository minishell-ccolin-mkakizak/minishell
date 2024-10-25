/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:31:44 by mkakizak          #+#    #+#             */
/*   Updated: 2024/10/25 10:03:54 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	check_p_tok(char c, va_list arg_ptr)
{
	if (c == 'c')
		return (ft_putchar(va_arg(arg_ptr, int)));
	else if (c == 's')
		return (ft_print_str(va_arg(arg_ptr, char *)));
	else if (c == 'p')
		return (ft_put_address((unsigned long)va_arg(arg_ptr, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(arg_ptr, int)));
	else if (c == 'u')
		return (ft_print_unsigned_dec((unsigned int)va_arg(arg_ptr, int)));
	else if (c == 'x')
		return (ft_print_lower_hex((unsigned int)va_arg(arg_ptr, int)));
	else if (c == 'X')
		return (ft_print_upper_hex((unsigned int)va_arg(arg_ptr, int)));
	else if (c == '%')
	{
		if (ft_putchar('%') != -1)
			return (1);
		else
			return (-1);
	}
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_ptr;
	int		res;
	int		prev_res;

	res = 0;
	va_start(arg_ptr, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (!*format++)
				return (res);
			prev_res = res;
			res += check_p_tok(*format, arg_ptr);
			if (res < prev_res)
				return (-1);
		}
		else if (ft_putchar(*format) == -1)
			return (-1);
		else
			res++;
		format++;
	}
	va_end(arg_ptr);
	return (res);
}
