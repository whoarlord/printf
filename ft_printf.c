/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:39:17 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 10:55:22 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_calculate_digits_hex(unsigned long long nb)
{
	int	result;

	result = 1;
	while (nb > 15)
	{
		nb = nb / 16;
		result++;
	}
	return (result);
}

int	ft_calculate_digits(unsigned int nb)
{
	int	result;

	result = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		result++;
	}
	return (result);
}

char	*ft_number_to_base(unsigned long long nb, int size, const char *base)
{
	char	*result;
	int		i;
	int		base_size;

	i = 1;
	result = (char *)malloc(size + 1);
	base_size = ft_strlen(base);
	while (nb > (unsigned long long)base_size - 1)
	{
		result[size - i] = base[(nb % base_size)];
		i++;
		nb = nb / base_size;
	}
	result[size - i] = base[(nb % base_size)];
	result[size] = '\0';
	return (result);
}

int	check_type(va_list vargs, char *s, int i)
{
	int		result;
	t_flags	*flags;

	result = 0;
	flags = (t_flags *)ft_calloc(sizeof(t_flags), 1);
	flags = ft_fill_flags(s, flags);
	if (s[i] == 'c')
		return (ft_putchar_fd(va_arg(vargs, int), 1), 1);
	if (s[i] == 's')
		result = ft_printstr(va_arg(vargs, char *), flags);
	if (s[i] == 'p')
		result = ft_printptr(va_arg(vargs, unsigned long), flags);
	if (s[i] == 'd' || s[i] == 'i')
		result = ft_printnbr(va_arg(vargs, int), flags);
	if (s[i] == 'u')
		result = ft_print_unnbr(va_arg(vargs, unsigned int), flags);
	if (s[i] == 'x')
		result = ft_print_hex(va_arg(vargs, unsigned int),
				flags, "0123456789abcdef");
	if (s[i] == 'X')
		result = ft_print_hex(va_arg(vargs, unsigned int),
				flags, "0123456789ABCDEF");
	free(s);
	free(flags);
	return (result);
}

int	ft_printf(char const *s, ...)
{
	int		result;
	va_list	vargs;
	char	*specifiers;
	int		i;

	va_start(vargs, s);
	result = 0;
	i = 0;
	specifiers = "cspdiuxX%";
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			while (!ft_strchr(specifiers, s[i]))
				i++;
			result = result + check_type(vargs, ft_substr(s, 0, i + 1), i);
			s = s + i;
			i = 0;
		}
		else
		{
			write(1, s, 1);
			result++;
		}
		s++;
	}
	va_end(vargs);
	return (result);
}

/* int	main(void)
{
	char *result;
	int nb;

	result = "Hola";
	nb = 10123213;
	ft_printf("size: %d\n", ft_printf("|%10.4s|\n", result));
	printf("size: %d\n", printf("|%10.4s|\n", result));
	ft_printf("size: %d\n", ft_printf("|%20p|\n", result));
	printf("size: %d\n", printf("|%20p|\n", result));
	ft_printf("size: %d\n", ft_printf("|%-010d|\n", nb));
	printf("size: %d\n", printf("|%-10d|\n", nb));
	ft_printf("size: %d\n", ft_printf("|%-#10X|\n", 1823947));
	printf("size: %d\n", printf("|%-#10X|\n", 1823947));
} */
