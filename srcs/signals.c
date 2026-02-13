/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:36:22 by jriga             #+#    #+#             */
/*   Updated: 2025/12/02 22:36:20 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

void					rl_replace_line(const char *text, int clear_undo);

static void	sigint_handler(int sig)
{
	(void)sig;
	g_signal_status = 130;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction");
	signal(SIGQUIT, SIG_IGN);
}

static int	handle_exit_status(int status)
{
	int	last_status;

	if (WIFEXITED(status))
		last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
	}
	else
		last_status = 1;
	return (last_status);
}

void	waitpid_func(int *status, int pid)
{
	pid_t		temp_pid;

	while (1)
	{
		temp_pid = waitpid(-1, &status[0], 0);
		if (temp_pid == -1)
			break ;
		if (temp_pid == pid)
		{
			status[1] = handle_exit_status(status[0]);
			if (status[0] == 256)
				status[1] = 127;
		}
	}
}

void	set_sig(void *sig)
{
	signal(SIGQUIT, sig);
	signal(SIGINT, sig);
}
