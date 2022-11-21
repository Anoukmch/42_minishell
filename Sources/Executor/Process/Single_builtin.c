#include "../../../includes/minishell.h"

static void	single_builtin_bis(int infd_tmp, int outfd_tmp)
{
	dup2(infd_tmp, STDIN_FILENO);
	close (infd_tmp);
	dup2(outfd_tmp, STDOUT_FILENO);
	close (outfd_tmp);
}

int	single_builtin(t_child *child, t_exec *exec, t_env *env)
{
	int	infd_tmp;
	int	outfd_tmp;

	infd_tmp = dup(STDIN_FILENO);
	outfd_tmp = dup(STDOUT_FILENO);
	if (get_infile(child))
		return (1);
	if (get_outfile(child))
		return (1);
	if (child->parser_redirect_input[0] != NULL)
		dup2(child->fd_in, STDIN_FILENO);
	if (child->parser_redirect_input[0] != NULL)
		close(child->fd_in);
	if (child->parser_redirect_output[0] != NULL)
		dup2(child->fd_out, STDOUT_FILENO);
	if (child->parser_redirect_output[0] != NULL)
		close(child->fd_out);
	if (exec->isheredoc == 1)
		unlink("heredoc");
	if (builtin_command(child, exec, env))
		return (1);
	single_builtin_bis(infd_tmp, outfd_tmp);
	return (0);
}
