/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:54:06 by ofadahun          #+#    #+#             */
/*   Updated: 2023/05/09 11:42:36 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/*
Evaluates bin to char and when char done,  write to stdout
Sends signal to client once whole message/string completed
*/
void	eval_bin_to_char(int sig_num, pid_t cpid)
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
		if (ch)
			write(STDOUT_FILENO, &ch, 1);
		bit = 0;
		if (!ch)
		{
			if (kill(cpid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		ch = 0;
	}
}

void	sig_handler(int sig_num, siginfo_t *siginfo, void *context)
{
	static int	cpid;

	cpid = siginfo -> si_pid;
	context = NULL;
	eval_bin_to_char(sig_num, cpid);
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
	act.sa_flags = SA_SIGINFO;
	act.sa_mask = mask;
	act.sa_sigaction = &sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
