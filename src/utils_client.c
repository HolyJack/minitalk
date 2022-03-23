/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:43:42 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/23 13:08:26 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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

int	ft_atoi(const char *s)
{
	int		buf;
	int		sign;
	char	*str;

	sign = 1;
	str = (char *) s;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\f' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	buf = 0;
	while (ft_isdigit(*str) == 1)
	{
		buf *= 10;
		buf += (*str - '0');
		str++;
	}
	return (sign * buf);
}
