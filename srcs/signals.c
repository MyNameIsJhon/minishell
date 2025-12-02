/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:36:22 by jriga             #+#    #+#             */
/*   Updated: 2025/12/02 22:22:32 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

volatile sig_atomic_t signal_status = 0;

void rl_replace_line(const char *text, int clear_undo);

static void sigint_handler(int sig)
{
	(void)sig;
	signal_status = 130;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void set_signal_sigint(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sa->sa_handler = sigint_handler;
	if (sigaction(SIGINT, sa, NULL) == -1)
		perror("sigaction");
}

/* static void sigint_handler(int sig) */
/* { */
/* 	(void)sig; */
/* 	signal_status = 130; */
/* 	ft_putchar('\n'); */
/* 	rl_on_new_line(); */
/* 	rl_replace_line("", 0); */
/* 	rl_redisplay(); */
/* } */
/**/
/* static void set_signal_sigint(struct sigaction *sa) */
/* { */
/* 	sigemptyset(&sa->sa_mask); */
/* 	sa->sa_flags = 0; */
/* 	sa->sa_handler = sigint_handler; */
/* 	if (sigaction(SIGINT, sa, NULL) == -1) */
/* 		perror("sigaction"); */
/* } */
void init_signals()
{
	struct sigaction sa;
	set_signal_sigint(&sa);
}
