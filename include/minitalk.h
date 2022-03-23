/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:54:54 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/23 16:26:06 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <libft.h>
# include <signal.h>

typedef struct s_sdata
{
	char	*str;
	int		c;
	int		bits;
	int		pid;
}	t_sdata;

typedef struct s_cdata
{
	char	*str;
	int		i;
	int		pid;
}	t_cdata;

#endif
