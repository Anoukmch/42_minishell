#include "../../includes/minishell.h"

int	g_exit_code = 0;

void	initialize_struct(t_child	***child, t_exec **exec, t_lex *lex)
{
	*child = initialize_child(lex);
	*exec = initialize_exec(lex);
	if (!(*child) || !(*exec))
	{
		free_struct(*child, *exec, lex);
		perror_exit_status(NULL, "check init", 1);
	}
}

void	wait_child(t_exec *exec, t_lex *lex, t_child **child)
{
	int	tmp;

	tmp = 0;
	if (lex->no_processes == 1 && child[0]->isbuiltin == true)
		return ;
	waitpid(exec->last_pid, &tmp, 0);
	while (wait(NULL) > 0)
		continue ;
	if (WIFSIGNALED(tmp))
		g_exit_code = 128 + WTERMSIG(tmp);
	else if (WIFEXITED(tmp))
		g_exit_code = WEXITSTATUS(tmp);
}

void	enter_shell(t_env *env)
{
	t_lex	*lex;
	t_child	**child;
	t_exec	*exec;

	handle_signals();
	lex = initialize_lex();
	if (lex)
	{
		add_history(lex->line);
		initialize_struct(&child, &exec, lex);
		if (!parser(lex, child, env))
		{
			free_struct(NULL, NULL, lex);
			executor(child, exec, env);
			wait_child(exec, lex, child);
		}
		free_struct(child, exec, NULL);
	}
}

int	main(int ac, char **ag, char **envp)
{
	t_env	*env;

	if (ac != 1 || !ag[0])
		return (perror_return_status(NULL, "arg number incorrect", 1));
	signal(SIGQUIT, SIG_IGN);
	env = initialize_env(envp);
	if (!env)
		return (perror_return_status(NULL, "check init", 1));
	while (1)
		enter_shell(env);
	free_env(env);
	return (0);
}
