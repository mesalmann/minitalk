/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:45:15 by mesalman          #+#    #+#             */
/*   Updated: 2025/11/09 17:05:35 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	g_message_done = 0;

void	get_cpid(int sig, int *cpid, pid_t *pid)
{
	if (sig == SIGUSR1)
		*pid |= 1 << (31 - *cpid);
	(*cpid)++;
}

void	get_message(int sig, pid_t pid)
{
	static unsigned char	c = 0;
	static int				bit = 0;

	if (sig == SIGUSR1)
		c |= 1 << (7 - bit);
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(pid, SIGUSR1);
			g_message_done = 1;
		}
		else
		{
			write(1, &c, 1);
			kill(pid, SIGUSR1);
		}
		bit = 0;
		c = 0;
	}
}

void	print_bit(int sig)
{
	static int		cpid = 0;
	static pid_t	pid = 0;

	if (cpid < 32)
		get_cpid(sig, &cpid, &pid);
	else
		get_message(sig, pid);
	if (g_message_done)
	{
		cpid = 0;
		pid = 0;
		g_message_done = 0;
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &print_bit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(1, "ERROR\n", 6);
		exit(EXIT_FAILURE);
	}	
}

void	print_pid(void)
{
	pid_t	pid;

	pid = getpid();
	write(1, "Server PID =", 12);
	ft_putnbr(pid);
	write(1, "\n", 1);
}

int	main(void)
{
	print_pid();
	setup_signals();
	while (1)
		pause();
	return (0);
}
