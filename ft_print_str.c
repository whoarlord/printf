/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:13:10 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 19:22:32 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *input, t_flags *flags)
{
	int	size;
	int	result_state;

	result_state = 0;
	size = 0;
	if (!input)
	{
		input = ft_strdup("(null)");
		result_state = 1;
	}
	if (!flags->precision_exist)
		flags->precision = ft_strlen(input);
	if (flags->precision < 6 && ft_strnstr(input, "(null)", 6))
		ft_bzero(input, 6);
	if (ft_strlen(input) < (size_t)flags->precision)
		flags->precision = ft_strlen(input);
	if (flags->precision < flags->width)
		size = flags->width;
	else
		size = flags->precision;
	ft_fill_str(flags, input);
	if (result_state)
		free(input);
	return (size);
}

void	ft_fill_str(t_flags *flags, char *input)
{
	if (flags->align_left)
	{
		ft_print_input(input, flags->precision);
		ft_print_spaces(flags->width - flags->precision);
		return ;
	}
	ft_print_spaces(flags->width - flags->precision);
	ft_print_input(input, flags->precision);
}

void	ft_print_spaces(int size)
{
	while (size > 0)
	{
		ft_putchar_fd(' ', 1);
		size--;
	}
}

void	ft_print_zeros(int size)
{
	while (size > 0)
	{
		ft_putchar_fd('0', 1);
		size--;
	}
}

void	ft_print_input(char *input, int size)
{
	while (*input && size > 0)
	{
		ft_putchar_fd(*input, 1);
		size--;
		input++;
	}
}
