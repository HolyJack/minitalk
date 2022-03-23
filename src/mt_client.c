/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:35:35 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/23 16:37:34 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_cdata	g_cdata;

void	sig_process(int signal, siginfo_t *info, void *context)
{
	int	answer;

	(void) signal;
	(void) context;
	if (g_cdata.pid != info->si_pid)
		return ;
	if (g_cdata.i)
	{
		if (g_cdata.i & *(g_cdata.str))
			answer = SIGUSR1;
		else
			answer = SIGUSR2;
		(g_cdata.i) >>= 1;
	}
	else if (*(++g_cdata.str))
	{
		g_cdata.i = 0b10000000;
		answer = SIGUSR1;
	}
	else
		answer = SIGUSR2;
	kill(g_cdata.pid, answer);
}

void	sig_exit(int signal)
{
	(void) signal;
	ft_printf("Transition is over!\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act1;
	struct sigaction	act2;

	if (argc != 3)
		return (0);
	g_cdata.str = argv[2];
	g_cdata.i = 0b10000000;
	g_cdata.pid = ft_atoi(argv[1]);
	act1.sa_flags = SA_SIGINFO;
	act1.sa_sigaction = &sig_process;
	act2.sa_handler = &sig_exit;
	sigaction(SIGUSR1, &act1, NULL);
	sigaction(SIGUSR2, &act2, NULL);
	kill(g_cdata.pid, SIGUSR1);
	if (usleep(1000) == 0)
		return (1);
	while (1)
		pause();
	return (0);
}
