/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:05:55 by airandri          #+#    #+#             */
/*   Updated: 2026/03/29 06:44:10 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_putnbr_hexa_min(unsigned int nb);
int		ft_putnbr_hexa_maj(unsigned int nb);
int		ft_putnbr(int nb);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putptr(unsigned long ptr);
int		ft_putnbr_unsigned(unsigned int n);
char	*ft_unsigned_itoa(unsigned int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

#endif
