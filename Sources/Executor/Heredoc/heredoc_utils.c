#include "../../../includes/minishell.h"

int	line_null_hd(t_child *child, char *temp, int file)
{
	dup2(child->set_stdin_back, STDIN_FILENO);
	close(child->set_stdin_back);
	unlink("heredoc");
	g_exit_code = 1;
	return (close_free(child, temp, file, 1));
}

int	close_free(t_child *child, char *temp, int file, int status)
{
	close(file);
	free(temp);
	free(child->heredoc_line);
	return (status);
}
