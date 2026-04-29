/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:06:13 by airandri          #+#    #+#             */
/*   Updated: 2026/02/28 20:07:09 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_formats(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		len += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		len += ft_putnbr_hexa_min(va_arg(args, unsigned int));
	else if (format == 'X')
		len += ft_putnbr_hexa_maj(va_arg(args, unsigned int));
	else if (format == 'p')
		len += ft_putptr(va_arg(args, unsigned long));
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		total_len;

	i = 0;
	total_len = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			total_len += ft_formats(args, format[i + 1]);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			total_len++;
		}
		i++;
	}
	va_end(args);
	return (total_len);
}
