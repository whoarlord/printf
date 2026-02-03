/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:09:10 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 16:54:00 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_chr(t_flags *flags, int chr, int size)
{
	int		i;

	i = 0;
	if (flags->align_left)
	{
		ft_putchar_fd(chr, 1);
		while (i < size - flags->precision)
		{
			ft_putchar_fd(' ', 1);
			i++;
		}
		return ;
	}
	while (i < size - flags->precision)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd(chr, 1);
}

int	ft_printchr(int chr, t_flags *flags)
{
	int	size;

	size = 1;
	if (!flags->precision_exist)
		flags->precision = 1;
	if (1 < flags->precision)
		flags->precision = 1;
	if (flags->precision < flags->width)
		size = flags->width;
	else
		size = flags->precision;
	ft_put_chr(flags, chr, size);
	return (size);
}
