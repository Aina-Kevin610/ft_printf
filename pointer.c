/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:51:36 by airandri          #+#    #+#             */
/*   Updated: 2026/02/26 11:04:32 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printptr(unsigned long nb)
{
	int		len;
	char	*base;

	base = "0123456789abcdef";
	len = 0;
	if (nb >= 16)
		len = ft_printptr(nb / 16);
	len += ft_putchar(base[nb % 16]);
	return (len);
}

int	ft_putptr(unsigned long ptr)
{
	int	len;

	len = 2;
	if (!ptr)
	{
		len = ft_putstr("(nil)");
		return (len);
	}
	ft_putstr("0x");
	len += ft_printptr(ptr);
	return (len);
}
