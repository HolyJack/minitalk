/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:54:54 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/23 13:09:01 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define BUFSIZE 2048

# include <stdio.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_data
{
	char	str[BUFSIZE];
	int		c;
	int		s_index;
	int		bits;
	int		pid;
}	t_data;

typedef struct s_cdata
{
	char	*str;
	int		i;
	int		pid;
}	t_cdata;

int		ft_atoi(const char *s);
int		ft_putstr(char *str);
void	ft_putnbr(int n);

#endif
