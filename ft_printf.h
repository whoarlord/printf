/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:13:32 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 19:30:53 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "./libft/libft.h"
# include <stdarg.h>
# include "limits.h"
# include <stdio.h>

typedef struct s_flags
{
	int		align_left;
	int		precision;
	int		precision_exist;
	int		width;
	int		sign;
	int		hash;
	int		space;
	char	insert_char[3];
	int		zeros;
}		t_flags;
char	*ft_number_to_base(unsigned long long nb, int size, const char *base);
int		ft_printstr(char *input, t_flags *flags);
int		ft_printptr(unsigned long long input, t_flags *flags);
int		ft_printnbr(int nb, t_flags *flags);
int		ft_print_unnbr(unsigned int nb, t_flags *flags);
int		ft_printchr(int chr, t_flags *flags);
int		ft_calculate_digits_hex(unsigned long long nb);
int		ft_calculate_digits(unsigned int nb);
int		check_type(va_list vargs, char *s, int i);
int		ft_printf(char const *s, ...);
int		ft_print_hex(unsigned int nb, t_flags *flags, char const *s);
t_flags	*ft_fill_flags(char *s, t_flags *result, char *specifiers);
void	ft_check_nbr(t_flags *flags, char *input, int size);
void	ft_fill_str(t_flags *flags, char *input);
void	ft_fill_ptr(t_flags *flags, char *input);
void	ft_fill_nbr(t_flags *flags, char *input, int size);
void	ft_fill_zeros(t_flags *flags);
char	*ft_strjoin_len(char *s1, const char *s2, size_t len);
void	ft_print_spaces(int size);
void	ft_print_zeros(int size);
void	ft_print_input(char *input, int size);

#endif
