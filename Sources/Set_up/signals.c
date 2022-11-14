

#include "../../includes/minishell.h"

int exit_code;

static void	control_c(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_code = 1;
	}
// 	else if (signum == SIGABRT)
// 		errorexit("CTRL-D");
}

/*
	ECHOCTL: controls characters with '^'?  echo control chars as ^(Char)
	followed by the corresponding text character
	&= ~ --> HIDE characters/ turn off
	|= --> ENABLE characters
	c_lflag --> local modes, echo in c_lflag controls whether input is
	immediately reechoed as output
	tcgetattr --> get the parameters associated with the terminal,
		stores them in termios struct
	tcsetattr--> set the parameters associated with the terminal
		from termios struct
	TCSANOW --> make change immediately
	SIGINT --> CTRL-C
	SIGABRT --> CTRL-BACKSLASH
	SIGQUIT --> CTRL-D
*/
void	handle_signals(void)
{
	struct sigaction	sa;
	struct termios		te;

	tcgetattr(0, &te);
	te.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &te);
	sa.sa_handler = &control_c;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
