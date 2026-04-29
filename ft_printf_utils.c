/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 07:38:25 by airandri          #+#    #+#             */
/*   Updated: 2026/02/26 11:22:35 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	len;

	if (!s)
	{
		ft_putstr_fd ("(null)", 1);
		return (6);
	}
	ft_putstr_fd (s, 1);
	len = (int)ft_strlen (s);
	return (len);
}

int	ft_putnbr(int n)
{
	char	*nb;
	int		len;

	nb = ft_itoa (n);
	if (!nb)
		return (0);
	ft_putstr_fd (nb, 1);
	len = (int)ft_strlen (nb);
	free (nb);
	return (len);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	char	*nb;
	int		len;

	nb = ft_unsigned_itoa (n);
	if (!nb)
		return (0);
	ft_putstr_fd (nb, 1);
	len = (int)ft_strlen (nb);
	free (nb);
	return (len);
}
