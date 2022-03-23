/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:35:18 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/23 13:07:41 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

void	mt_initdata(void)
{
	g_data.c = 0;
	g_data.str[0] = 0;
	g_data.s_index = 0;
	g_data.bits = 0;
	g_data.pid = -1;
}

void	active_transition(int signal)
{
	if (signal == SIGUSR1)
			g_data.c = g_data.c << 1 | 0b1;
	if (signal == SIGUSR2)
			g_data.c = g_data.c << 1 | 0b0;
	if (!--g_data.bits)
	{
		g_data.str[g_data.s_index] = g_data.c;
		g_data.c = 0b0;
		g_data.s_index++;
		g_data.str[g_data.s_index] = 0;
	}
	kill(g_data.pid, SIGUSR1);
}

void	change_transition_status(int signal)
{
	if (signal == SIGUSR1)
	{
		g_data.bits = 8;
		kill(g_data.pid, SIGUSR1);
	}
	else if (signal == SIGUSR2)
	{
		ft_putstr(g_data.str);
		ft_putstr("\n");
		kill(g_data.pid, SIGUSR2);
		mt_initdata();
	}
}

void	mt_sighandler(int signal, siginfo_t *info, void *context)
{
	(void) context;
	if (g_data.pid == -1 && signal == SIGUSR1)
		g_data.pid = info->si_pid;
	if (info->si_pid != g_data.pid)
		return ;
	if (g_data.bits)
		active_transition(signal);
	else
		change_transition_status(signal);
}

int	main(void)
{
	const int			pid = getpid();
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &mt_sighandler;
	mt_initdata();
	ft_putnbr(pid);
	ft_putstr("\n");
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
