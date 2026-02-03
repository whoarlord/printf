/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:39:17 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 16:48:13 by iarrien-         ###   ########.fr       */
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
	flags = ft_fill_flags(s, flags, "cspdiuxX");
	if (s[i] == 'c')
		result = ft_printchr(va_arg(vargs, int), flags);
	else if (s[i] == 's')
		result = ft_printstr(va_arg(vargs, char *), flags);
	else if (s[i] == 'p')
		result = ft_printptr(va_arg(vargs, unsigned long), flags);
	else if (s[i] == 'd' || s[i] == 'i')
		result = ft_printnbr(va_arg(vargs, int), flags);
	else if (s[i] == 'u')
		result = ft_print_unnbr(va_arg(vargs, unsigned int), flags);
	else if (s[i] == 'x')
		result = ft_print_hex(va_arg(vargs, unsigned int),
				flags, "0123456789abcdef");
	else if (s[i] == 'X')
		result = ft_print_hex(va_arg(vargs, unsigned int),
				flags, "0123456789ABCDEF");
	else if (s[i] == '%')
		return (ft_putchar_fd('%', 1), free(flags), free(s), 1);
	return (free(s), free(flags), result);
}

int	ft_printf(char const *s, ...)
{
	int		result;
	va_list	vargs;
	int		i;

	va_start(vargs, s);
	result = 0;
	i = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			while (!ft_strchr("cspdiuxX%%", s[i]))
				i++;
			result = result + check_type(vargs, ft_substr(s, 0, i + 1), i);
			s = s + i;
			i = 0;
		}
		else
			result = result + write(1, s, 1);
		s++;
	}
	return (va_end(vargs), result);
}

/* int	main(void)
{
	char *result;
	int nb;

	result = "Hola";
	nb = 10123213;
	ft_printf("size: %d\n", ft_printf("|%-10.8s|\n", result));
	printf("size: %d\n", printf("|%-10.8s|\n", result));
	ft_printf("size: %d\n", ft_printf("|%8.4p|\n", result));
	printf("size: %d\n", printf("|%8p|\n", result));
	ft_printf("size: %d\n", ft_printf("|%+30d|\n", nb));
	printf("size: %d\n", printf("|%+30d|\n", nb));
	ft_printf("size: %d\n", ft_printf("|%+30.0d|\n", 1));
	printf("size: %d\n", printf("|%+30.0d|\n", 1));
	ft_printf("size: %d\n", ft_printf("|%#30X|\n", 0));
	printf("size: %d\n", printf("|%#30X|\n", 0));

	int ret1;
    int ret2;

    // =====================
    // === CHARACTERS =========
    // =====================
    printf("\n=== CHAR ===\n");

    ret1 = printf("printf  : |%c|\n", 'A');
    ret2 = ft_printf("ft_print: |%c|\n", 'A');
    printf("ret: %d | %d\n", ret1, ret2);

    // =====================
    // === STRINGS =========
    // =====================
    printf("\n=== STRING ===\n");

    ret1 = printf("printf  : |%10s|\n", "hola");
    ret2 = ft_printf("ft_print: |%10s|\n", "hola");
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%-10s|\n", "hola");
    ret2 = ft_printf("ft_print: |%-10s|\n", "hola");
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%.3s|\n", "abcdef");
    ret2 = ft_printf("ft_print: |%.3s|\n", "abcdef");
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%10.3s|\n", "abcdef");
    ret2 = ft_printf("ft_print: |%10.3s|\n", "abcdef");
    printf("ret: %d | %d\n", ret1, ret2);

	char *inp = NULL;
	ret1 = printf("printf  : |%.6s|\n", inp);
	ret2 = ft_printf("ft_print: |%.6s|\n", inp);
    printf("ret: %d | %d\n", ret1, ret2);

    // =====================
    // === INTEGERS =========
    // =====================
    printf("\n=== INT ===\n");

    ret1 = printf("printf  : |%d|\n", 42);
    ret2 = ft_printf("ft_print: |%d|\n", 42);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%+d|\n", 42);
    ret2 = ft_printf("ft_print: |%+d|\n", 42);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |% d|\n", 42);
    ret2 = ft_printf("ft_print: |% d|\n", 42);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%05d|\n", -42);
    ret2 = ft_printf("ft_print: |%05d|\n", -42);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%-8d|\n", 42);
    ret2 = ft_printf("ft_print: |%-8d|\n", 42);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%.0d|\n", 0);
    ret2 = ft_printf("ft_print: |%.0d|\n", 0);
    printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%1.0d|\n", 0);
    ret2 = ft_printf("ft_print: |%1.0d|\n", 0);
    printf("ret: %d | %d\n", ret1, ret2);

    // =====================
    // === UNSIGNED=========
    // =====================
    printf("\n=== UNSIGNED ===\n");

    ret1 = printf("printf  : |%u|\n", 4294967295U);
    ret2 = ft_printf("ft_print: |%u|\n", 4294967295U);
    printf("ret: %d | %d\n", ret1, ret2);

	unsigned int u1 = 0;
    unsigned int u2 = 42;
    unsigned int u3 = 4294967295U; // UINT_MAX

    ret1 = printf("printf  : |%.0u|\n", u1);
    ret2 = ft_printf("ft_print: |%.0u|\n", u1);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%5u|\n", u1);
    ret2 = ft_printf("ft_print: |%5u|\n", u1);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%8.5u|\n", u2);
    ret2 = ft_printf("ft_print: |%8.5u|\n", u2);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%8.5u|\n", u2);
    ret2 = ft_printf("ft_print: |%08.5u|\n", u2);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%-8.5u|\n", u2);
    ret2 = ft_printf("ft_print: |%-8.5u|\n", u2);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%u|\n", u3);
    ret2 = ft_printf("ft_print: |%u|\n", u3);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%15u|\n", u3);
    ret2 = ft_printf("ft_print: |%15u|\n", u3);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%.15u|\n", u3);
    ret2 = ft_printf("ft_print: |%.15u|\n", u3);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%-20.10u|\n", u2);
    ret2 = ft_printf("ft_print: |%-20.10u|\n", u2);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%010u|\n", u2);
    ret2 = ft_printf("ft_print: |%010u|\n", u2);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%5.0u|\n", u1);
    ret2 = ft_printf("ft_print: |%5.0u|\n", u1);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%0u|\n", u1);
    ret2 = ft_printf("ft_print: |%0u|\n", u1);
    printf("ret: %d | %d\n", ret1, ret2);

    // =====================
    // === HEXADECIMAL =========
    // =====================
    printf("\n=== HEX ===\n");

    ret1 = printf("printf  : |%x|\n", 1823947);
    ret2 = ft_printf("ft_print: |%x|\n", 1823947);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%#x|\n", 1823947);
    ret2 = ft_printf("ft_print: |%#x|\n", 1823947);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%#10X|\n", 1823947);
    ret2 = ft_printf("ft_print: |%#10X|\n", 1823947);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%-#10X|\n", 1823947);
    ret2 = ft_printf("ft_print: |%-#10X|\n", 1823947);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%#010X|\n", 1823947);
    ret2 = ft_printf("ft_print: |%#010X|\n", 1823947);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%#.0x|\n", 0);
    ret2 = ft_printf("ft_print: |%#.0x|\n", 0);
    printf("ret: %d | %d\n", ret1, ret2);

    // =====================
    // === POINTER =========
    // =====================
    printf("\n=== POINTER ===\n");

    int x = 42;
    ret1 = printf("printf  : |%p|\n", &x);
    ret2 = ft_printf("ft_print: |%p|\n", &x);
    printf("ret: %d | %d\n", ret1, ret2);

    ret1 = printf("printf  : |%p|\n", NULL);
    ret2 = ft_printf("ft_print: |%p|\n", NULL);
    printf("ret: %d | %d\n", ret1, ret2);

    // =====================
    // === %% =========
    // =====================
    printf("\n=== %% ===\n");

    ret1 = printf("printf  : |%%|\n");
    ret2 = ft_printf("ft_print: |%%|\n");
    printf("ret: %d | %d\n", ret1, ret2);

	// =====================
    // === COMPLEX =========
    // =====================
	printf("\n=== COMPLEX ===\n");

	ret1 = printf("printf  : |%.0d|\n", 0);
	ret2 = ft_printf("ft_print: |%.0d|\n", 0);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%5.0d|\n", 0);
	ret2 = ft_printf("ft_print: |%5.0d|\n", 0);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%#.0x|\n", 0);
	ret2 = ft_printf("ft_print: |%#.0x|\n", 0);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%8.5d|\n", 42);
	ret2 = ft_printf("ft_print: |%08.5d|\n", 42);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%-8d|\n", 42);
	ret2 = ft_printf("ft_print: |%-08d|\n", 42);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%+7.4d|\n", 42);
	ret2 = ft_printf("ft_print: |%+7.4d|\n", 42);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%+d|\n", 42);
	ret2 = ft_printf("ft_print: |% +d|\n", 42);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%#010x|\n", 42);
	ret2 = ft_printf("ft_print: |%#010x|\n", 42);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%#10.5x|\n", 42);
	ret2 = ft_printf("ft_print: |%#10.5x|\n", 42);
	printf("ret: %d | %d\n", ret1, ret2);

	x = 42;
	ret1 = printf("printf  : |%p|\n", &x);
	ret2 = ft_printf("ft_print: |%.5p|\n", &x);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%2d|\n", 12345);
	ret2 = ft_printf("ft_print: |%2d|\n", 12345);
	printf("ret: %d | %d\n", ret1, ret2);

	ret1 = printf("printf  : |%-+10.5d|\n", 42);
	ret2 = ft_printf("ft_print: |%0-+ #10.5d|\n", 42);
	printf("ret: %d | %d\n", ret1, ret2);

    ret2 = printf("%.4d%.2d%.20d%.0d%.0d%.d%.d%.d\n", 127, 0, 1023, 0, (int)-2147483648, 0, 1, (int)-2147483648);
    ret1 = ft_printf("%.4d%.2d%.20d%.0d%.0d%.d%.d%.d\n", 127, 0, 1023, 0, (int)-2147483648, 0, 1, (int)-2147483648);
    printf("ret: %d | %d\n", ret1, ret2);
    return 0;
} */

/* int main(void)
{
    int ret1;
    int ret2;

    ret1 = printf("%c%c%c*", '\0', '1', 1);
    ret2 = ft_printf("%c%c%c*", '\0', '1', 1);
    printf("ret: %d | %d\n", ret1, ret2);
} */
