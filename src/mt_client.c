/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:35:35 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/23 13:11:50 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_cdata	g_data;

void	sig_process(int signal, siginfo_t *info, void *context)
{
	int	answer;

	(void) signal;
	(void) context;
	if (g_data.pid != info->si_pid)
		return ;
	if (g_data.i)
	{
		if (g_data.i & *(g_data.str))
			answer = SIGUSR1;
		else
			answer = SIGUSR2;
		(g_data.i) >>= 1;
	}
	else if (*(++g_data.str))
	{
		g_data.i = 0b10000000;
		answer = SIGUSR1;
	}
	else
		answer = SIGUSR2;
	kill(g_data.pid, answer);
}

void	sig_exit(int signal)
{
	(void) signal;
	ft_putstr("Transition is over!\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act1;
	struct sigaction	act2;

	if (argc != 3)
		return (0);
	g_data.str = argv[2];
	g_data.i = 0b10000000;
	g_data.pid = ft_atoi(argv[1]);
	ft_putstr(g_data.str);
	ft_putstr("\n");
	act1.sa_flags = SA_SIGINFO;
	act1.sa_sigaction = &sig_process;
	act2.sa_handler = &sig_exit;
	sigaction(SIGUSR1, &act1, NULL);
	sigaction(SIGUSR2, &act2, NULL);
	kill(ft_atoi(argv[1]), SIGUSR1);
	if (usleep(500) == 0)
		return (0);
	while (1)
		pause();
	return (0);
}
