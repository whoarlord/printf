/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:12:20 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/02 17:44:51 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printptr(unsigned long long nb, t_flags *flags)
{
	int		size;
	char	*result;
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
	result = ft_fill_ptr(flags, temp, size);
	free(temp);
	ft_putstr_fd(result, 1);
	free(result);
	return (size);
}

char	*ft_fill_ptr(t_flags *flags, char *input, int size)
{
	char	*result;

	result = ft_calloc(size + 1, 1);
	if (flags->align_left)
	{
		ft_strlcpy(&result[0], input, ft_strlen(input) + 1);
		ft_memset(&result[ft_strlen(input)], ' ', size - ft_strlen(input));
		return (result);
	}
	ft_memset(&result[0], ' ', size - ft_strlen(input));
	ft_strlcpy(&result[size - ft_strlen(input)], input, ft_strlen(input) + 1);
	return (result);
}
