/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrien- <iarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:46:11 by iarrien-          #+#    #+#             */
/*   Updated: 2026/02/03 12:24:14 by iarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_insert_plus(t_flags *result)
{
	result->sign = 1;
	result->insert_char[0] = '+';
	result->insert_char[1] = '\0';
}

static int	ft_insert_precision(t_flags *result, char *s)
{
	result->precision = ft_atoi(s);
	result->precision_exist = 1;
	return (ft_calculate_digits(result->precision));
}

t_flags	*ft_fill_flags(char *s, t_flags *result, char *specifiers)
{
	int			i;

	i = 0;
	result->insert_char[0] = '\0';
	while (!(ft_strchr(specifiers, s[i])))
	{
		if (s[i] == '0' && !result->precision
			&& !result->width && !result->zeros)
			result->zeros = 1;
		else if (ft_isdigit(s[i]) && !result->width && !result->precision)
			result->width = ft_atoi(&s[i]);
		else if (s[i] == ' ')
			result->space = 1;
		else if (s[i] == '-')
			result->align_left = 1;
		else if (s[i] == '+')
			ft_insert_plus(result);
		else if (s[i] == '.')
			i = i + ft_insert_precision(result, &s[i + 1]);
		else if (s[i] == '#')
			result->hash = 1;
		i++;
	}
	return (result);
}

char	*ft_strjoin_len(char *s1, const char *s2, size_t len)
{
	char	*result;
	int		lens1;
	int		lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, lens1 + 1);
	ft_strlcpy(&result[lens1], s2, lens2 + 1);
	free(s1);
	return (result);
}
