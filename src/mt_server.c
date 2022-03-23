/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:35:18 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/23 17:08:53 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_sdata	g_sdata;

void	mt_initdata(void)
{
	g_sdata.c = 0;
	g_sdata.str = malloc(sizeof(char) * 1);
	g_sdata.str[0] = 0;
	g_sdata.bits = 0;
	g_sdata.pid = -1;
}

int	active_transition(int signal)
{
	char	*tmp;

	if (signal == SIGUSR1)
			g_sdata.c = g_sdata.c << 1 | 0b1;
	if (signal == SIGUSR2)
			g_sdata.c = g_sdata.c << 1 | 0b0;
	if (!--g_sdata.bits)
	{
		tmp = ft_strjoin(g_sdata.str, " ");
		tmp[ft_strlen(g_sdata.str)] = g_sdata.c;
		free(g_sdata.str);
		g_sdata.str = tmp;
		g_sdata.c = 0b0;
	}
	return (SIGUSR1);
}

int	change_transition_status(int signal)
{
	char	*tmp;

	if (signal == SIGUSR1)
		g_sdata.bits = 8;
	else if (signal == SIGUSR2)
	{
		tmp = g_sdata.str;
		ft_printf("%s\n", g_sdata.str);
		mt_initdata();
		free(tmp);
	}
	return (signal);
}

void	mt_sighandler(int signal, siginfo_t *info, void *context)
{
	int	ans;

	(void) context;
	ans = SIGUSR2;
	if (g_sdata.pid == -1 && signal == SIGUSR1)
		g_sdata.pid = info->si_pid;
	if (info->si_pid != g_sdata.pid)
		ans = SIGUSR2;
	else if (g_sdata.bits)
		ans = active_transition(signal);
	else
		ans = change_transition_status(signal);
	kill(info->si_pid, ans);
}

int	main(void)
{
	const int			pid = getpid();
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &mt_sighandler;
	mt_initdata();
	ft_printf("%d\n", pid);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
