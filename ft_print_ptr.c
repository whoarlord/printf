/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:12:20 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 18:41:13 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printptr(unsigned long long nb, t_flags *flags)
{
	int		size;
	char	*prefix;
	char	*input;
	char	*temp;

	prefix = ft_strdup("0x");
	size = ft_calculate_digits_hex(nb);
	input = ft_number_to_base(nb, size, "0123456789abcdef");
	if (nb == 0)
		temp = ft_strdup("(nil)");
	else
		temp = ft_strjoin(prefix, input);
	size = ft_strlen(temp);
	free(prefix);
	free(input);
	if (size < flags->width)
		size = flags->width;
	else
		flags->width = size;
	ft_fill_ptr(flags, temp);
	free(temp);
	return (flags->width);
}

void	ft_fill_ptr(t_flags *flags, char *input)
{
	if (flags->align_left)
	{
		ft_print_input(input, ft_strlen(input));
		ft_print_spaces(flags->width - ft_strlen(input));
		return ;
	}
	ft_print_spaces(flags->width - ft_strlen(input));
	ft_print_input(input, ft_strlen(input));
}
