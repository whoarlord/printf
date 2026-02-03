/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:02:39 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 19:41:25 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int nb, t_flags *flags)
{
	int		size;
	long	nb2;
	char	*input;

	nb2 = nb;
	size = 0;
	if (nb2 < 0)
	{
		nb2 = nb2 * -1;
		flags->insert_char[0] = '-';
	}
	else if (!flags->sign && flags->space == 1)
		flags->insert_char[0] = ' ';
	if (nb < 0 || (!flags->sign && flags->space == 1))
		flags->sign = 1;
	flags->insert_char[1] = '\0';
	flags->hash = 0;
	size = size + ft_calculate_digits((unsigned int)nb2);
	input = ft_number_to_base(nb2, size, "0123456789");
	if (!input)
		return (0);
	if (flags->width < size && !flags->precision_exist)
		flags->width = size;
	return (ft_check_nbr(flags, input, size), free(input), flags->width);
}

void	ft_check_nbr(t_flags *flags, char *input, int size)
{
	if (flags->precision_exist)
		flags->zeros = 0;
	else
		flags->precision = size;
	if (input[0] == '0' && flags->hash == 1)
	{
		flags->sign = 0;
		if (flags->width < flags->precision)
			flags->width = flags->precision;
		ft_fill_zeros(flags);
	}
	else if (input[0] == '0')
	{
		if (flags->width < flags->precision + flags->sign)
			flags->width = flags->precision + flags->sign;
		ft_fill_zeros(flags);
	}
	else
	{
		if (flags->precision < size)
			flags->precision = size;
		if (flags->width < flags->precision + flags->sign)
			flags->width = flags->precision + flags->sign;
		ft_fill_nbr(flags, input, size);
	}
}

void	ft_fill_nbr(t_flags *flags, char *input, int size)
{
	if (flags->align_left)
	{
		if (flags->sign)
			ft_print_input(flags->insert_char, ft_strlen(flags->insert_char));
		ft_print_zeros(flags->precision - size);
		ft_print_input(input, size);
		ft_print_spaces(flags->width - flags->precision - flags->sign);
		return ;
	}
	if (flags->zeros)
	{
		if (flags->sign)
			ft_print_input(flags->insert_char, ft_strlen(flags->insert_char));
		ft_print_zeros(flags->width - flags->precision - flags->sign);
	}
	else
	{
		ft_print_spaces(flags->width - flags->precision - flags->sign);
		if (flags->sign)
			ft_print_input(flags->insert_char, ft_strlen(flags->insert_char));
	}
	ft_print_zeros(flags->precision - size);
	ft_print_input(input, size);
}

void	ft_fill_zeros(t_flags *flags)
{
	if (flags->align_left)
	{
		if (flags->sign)
			ft_print_input(flags->insert_char, ft_strlen(flags->insert_char));
		ft_print_zeros(flags->precision);
		ft_print_spaces(flags->width - flags->precision);
		return ;
	}
	if (flags->zeros)
	{
		if (flags->sign)
			ft_print_input(flags->insert_char, ft_strlen(flags->insert_char));
		ft_print_zeros(flags->width - flags->sign);
	}
	else
	{
		ft_print_spaces(flags->width - flags->sign - flags->precision);
		if (flags->sign)
			ft_print_input(flags->insert_char, ft_strlen(flags->insert_char));
	}
	if (!flags->precision_exist && !flags->zeros)
		ft_print_zeros(1);
	else if (flags->precision_exist)
		ft_print_zeros(flags->precision);
}
