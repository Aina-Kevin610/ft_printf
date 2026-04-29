/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:09:11 by airandri          #+#    #+#             */
/*   Updated: 2026/02/26 11:04:24 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hexa_min(unsigned int nb)
{
	int		len;
	char	*base;

	base = "0123456789abcdef";
	len = 0;
	if (nb >= 16)
		len = ft_putnbr_hexa_min(nb / 16);
	len += ft_putchar(base[nb % 16]);
	return (len);
}

int	ft_putnbr_hexa_maj(unsigned int nb)
{
	int		len;
	char	*base;

	base = "0123456789ABCDEF";
	len = 0;
	if (nb >= 16)
		len = ft_putnbr_hexa_maj(nb / 16);
	len += ft_putchar(base[nb % 16]);
	return (len);
}
