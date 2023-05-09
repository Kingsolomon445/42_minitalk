/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:54:06 by ofadahun          #+#    #+#             */
/*   Updated: 2023/05/09 11:42:09 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int sig_num)
{
	static unsigned char	ch;
	static int				bit;

	if (sig_num == SIGUSR1)
		ch |= (1 << bit);
	else if (sig_num == SIGUSR2)
		ch &= (~(1 << bit));
	bit++;
	if (bit == 8)
	{
		write(STDOUT_FILENO, &ch, 1);
		ch = 0;
		bit = 0;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;
	sigset_t			mask;

	if (argc != 1)
	{
		ft_printf("Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	ft_printf("%s's PID -> %d\n", argv[0] + 2, getpid());
	sigemptyset(&mask);
	act.sa_handler = sig_handler;
	act.sa_flags = 0;
	act.sa_mask = mask;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
