/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:13:10 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/02 16:54:00 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *input, t_flags *flags)
{
	char	*result;
	int		size;

	size = 0;
	if (!input)
		input = ft_strdup("(null)");
	if (flags->precision < 6 && ft_strnstr(input, "(null)", 6))
		ft_bzero(input, 6);
	if (!flags->precision_exist)
		flags->precision = ft_strlen(input);
	if (ft_strlen(input) < (size_t)flags->precision)
		flags->precision = ft_strlen(input);
	if (flags->precision < flags->width)
		size = flags->width;
	else
		size = flags->precision;
	result = ft_fill_str(flags, input, size);
	ft_putstr_fd(result, 1);
	free(result);
	return (size);
}

char	*ft_fill_str(t_flags *flags, char *input, int size)
{
	char	*result;

	result = (char *) ft_calloc(size + 1, 1);
	if (flags->align_left)
	{
		ft_strlcpy(&result[0], input, flags->precision + 1);
		ft_memset(&result[flags->precision], ' ', size - flags->precision);
		result[size] = '\0';
		return (result);
	}
	ft_memset(&result[0], ' ', size - flags->precision);
	ft_strlcpy(&result[size - flags->precision], input, flags->precision + 1);
	return (result);
}
