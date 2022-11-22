/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:26:33 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/22 15:26:34 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	control_c(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 1;
	}
}

void	control_c_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_exit_code = 1;
	}
}

void	handle_signals_heredoc(void)
{
	struct sigaction	sa;
	struct termios		te;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&te, 0, sizeof(te));
	tcgetattr(0, &te);
	te.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &te);
	sa.sa_handler = &control_c_heredoc;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_signals(void)
{
	struct sigaction	sa;
	struct termios		te;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&te, 0, sizeof(te));
	tcgetattr(0, &te);
	te.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &te);
	sa.sa_handler = &control_c;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
