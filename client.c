/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:12:18 by mesalman          #+#    #+#             */
/*   Updated: 2025/11/09 17:06:59 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t    g_sig_control;

void    handler(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)info;
    (void)context;
    g_sig_control = 1;
}

void	send_bit(pid_t pid, char c)
{
	int	bit;
	
	g_sig_control = 0;
	bit = 0;
	while (bit <= 7)
	{
		if ((c >> (7- bit)) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_sig_control)
			pause();
		g_sig_control = 0;
		bit++;
	}
}

int	main(int ac, char **av)
{
	char	*str;
	int		i;
	pid_t	pid;
	struct sigaction	sa;
	if (ac != 3)
		return (0);
	pid = ft_atoi(av[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	str = av[2];
	i = 0;
	while (str[i])
	{
		send_bit(pid, str[i]);
		i++;
	}
	send_bit(pid, '\0');
	return (0);
}
