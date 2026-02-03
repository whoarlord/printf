/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unnbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:54:53 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 13:50:09 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unnbr(unsigned int nb, t_flags *flags)
{
	int		size;
	char	*input;
	char	*temp;

	size = ft_calculate_digits(nb);
	input = ft_number_to_base(nb, size, "0123456789");
	flags->sign = 0;
	flags->space = 0;
	flags->hash = 0;
	if (flags->width < size && !flags->precision_exist)
		flags->width = size;
	temp = ft_check_nbr(flags, input, size);
	ft_putstr_fd(temp, 1);
	free(input);
	free(temp);
	return (flags->width);
}
