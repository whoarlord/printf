/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:45:28 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 13:50:32 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int nb, t_flags *flags, char const *s)
{
	int		size;
	char	*input;
	char	*result;

	result = "";
	input = "";
	size = ft_calculate_digits_hex(nb);
	input = ft_number_to_base(nb, size, s);
	if (flags->hash)
	{
		flags->sign = 1;
		flags->insert_char[0] = '0';
		if (s[15] == 'F')
			flags->insert_char[1] = 'X';
		else
			flags->insert_char[1] = 'x';
		flags->insert_char[2] = '\0';
	}
	if (flags->width < size && !flags->precision_exist)
		flags->width = size;
	result = ft_check_nbr(flags, input, size);
	ft_putstr_fd(result, 1);
	free(result);
	free(input);
	return (flags->width);
}
