/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:02:39 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 10:53:29 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int nb, t_flags *flags)
{
	int		size;
	long	nb2;
	char	*input;
	char	*temp;

	nb2 = nb;
	size = 0;
	if (nb2 < 0)
	{
		nb2 = nb2 * -1;
		flags->insert_char[0] = '-';
		flags->sign = 1;
	}
	else if (!flags->sign && flags->space == 1)
	{
		flags->insert_char[0] = ' ';
		flags->sign = 1;
	}
	flags->insert_char[1] = '\0';
	size = size + ft_calculate_digits((unsigned int)nb2);
	input = ft_number_to_base(nb2, size, "0123456789");
	temp = ft_check_nbr(flags, input, size);
	ft_putstr_fd(temp, 1);
	free(input);
	free(temp);
	return (flags->width);
}

char	*ft_check_nbr(t_flags *flags, char *input, int size)
{
	char	*temp;

	temp = NULL;
	if (flags->precision_exist)
		flags->zeros = 0;
	else
		flags->precision = size;
	if (input[0] == '0' && flags->precision == 0)
		temp = ft_fill_zeros(flags);
	else if (input[0] == '0' && flags->hash == 1)
	{
		flags->sign = 0;
		temp = ft_fill_zeros(flags);
	}
	else
	{
		if (flags->precision < size)
			flags->precision = size;
		if (flags->width < size)
			flags->width = size;
		temp = ft_fill_nbr(flags, input, size);
	}
	return (temp);
}

char	*ft_fill_nbr(t_flags *flags, char *input, int size)
{
	char *result;
	char *temp;

	result = ft_calloc(flags->width + 1, 1);
	temp = malloc(flags->width + 1);
	if (flags->align_left)
	{
		if (flags->sign)
		{
			free(result);
			temp[0] = '\0';
			result = ft_strjoin_len(temp, &flags->insert_char[0], flags->width);
		}
		ft_memset(&result[flags->sign + flags->hash], '0', flags->precision - size);
		ft_strlcpy(&result[flags->precision - size + flags->sign + flags->hash], input, size + 1);
		ft_memset(&result[flags->precision], ' ',flags->width - flags->precision);
		return (free(temp), result);
	}
	if (flags->zeros)
		ft_memset(temp, '0',flags->width - flags->precision);
	else
		ft_memset(temp, ' ',flags->width - flags->precision);
	if (!flags->sign)
		flags->insert_char[0] = '\0';
	free(result);
	temp[flags->width - flags->precision] = '\0';
	result = ft_strjoin_len(temp, &flags->insert_char[0], flags->width);
	free(temp);
	ft_memset(&result[flags->sign + flags->hash], '0', flags->precision - size);
	ft_strlcpy(&result[flags->width - size + flags->sign + flags->hash], input, size + 1);
	return (result);
}

char	*ft_fill_zeros(t_flags *flags)
{
	char *result;
	char *temp;

	result = ft_calloc(flags->width + 1, 1);
	temp = malloc(flags->width + 1);
	if (flags->align_left)
	{
		if (flags->sign)
		{
			free(result);
			temp[0] = '\0';
			result = ft_strjoin_len(temp, &flags->insert_char[0], flags->width);
		}
		ft_memset(&result[flags->sign], '0', flags->precision);
		ft_memset(&result[flags->precision + flags->sign], ' ',flags->width - flags->precision);
		return (free(temp), result);
	}
	if (flags->zeros)
		ft_memset(temp, '0',flags->width - flags->sign - flags->precision);
	else
		ft_memset(temp, ' ',flags->width - flags->sign - flags->precision);
	if (!flags->sign)
		flags->insert_char[0] = '\0';
	ft_memset(&temp[flags->width - flags->sign - flags->precision], '0', flags->precision);
	temp[flags->width] = '\0';
	free(result);
	result = ft_strjoin_len(temp, &flags->insert_char[0], flags->width);
	free(temp);
	return (result);
}
