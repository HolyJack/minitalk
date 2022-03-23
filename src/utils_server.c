/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 04:15:46 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/23 13:06:44 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

int	ft_putstr(char *str)
{
	int	len;

	len = write(1, str, ft_strlen(str));
	return (len);
}

int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	while (++len && n)
		n /= 10;
	return (len);
}

void	ft_putnbr(int n)
{
	int			i;
	const int	len = ft_nbrlen(n);
	char		buf[11];

	buf[len] = 0;
	i = (int) len;
	while (n)
	{
		buf[--i] = n % 10 + '0';
		n /= 10;
	}
	ft_putstr(buf);
}
