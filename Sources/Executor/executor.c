
#include "../../includes/minishell.h"

int	here_doc(char *limiter, int i, int nbr_elements)
{
    int		file;
    char	*line;
	char	*temp;
    int		set_stdin_back;

    line = NULL;
    // what happens if we don't have permissions for heredoc or
    // heredoc exists?
    file = open("heredoc", O_CREAT | O_WRONLY
            | O_TRUNC, 0644);
    if (file < 0)
        return (1);
    // if (child[k]-->heredoc_quotes == 0)
    //  expand variables in heredoc
    // if (child[k]-->heredoc_quotes == 1)
    //  DO NOT expand variables in heredoc
	temp = ft_strjoin(limiter, "\n");
    set_stdin_back = dup(STDIN_FILENO);
    while (ft_strncmp(line, temp, (ft_strlen(limiter) + 1)))
    {
        handle_signals_heredoc(); //closing stdin --> closing readline
        if (i == nbr_elements - 2 && line)
            ft_putstr_fd(line, file);
        free(line);
        line = readline("Heredoc> ");
        if (!line) //ctrl c & ctrl d give NULL back
        {
            dup2(set_stdin_back, STDIN_FILENO); //set stdin back --> minishell is not closed
            close(set_stdin_back);
			free(line);
    		close(file);
    		if (i < nbr_elements - 2)
        		unlink("heredoc");
            if (isatty(STDERR_FILENO)) //CTRL-D referrs to STDERR??
                return (1); /* exit code 0 ? */
            return (1);
        }
        line = ft_strjoin(line, "\n");
    }
    free(line);
	free(temp);
    close(file);
    if (i < nbr_elements - 2)
        unlink("heredoc");
    return (0);
}

int	get_heredoc(t_child *child, t_exec *exec)
{
    int	i;
    int	nbr_elements;

    i = 0;
    nbr_elements = 0;
    while (child->parser_redirect_input[nbr_elements])
        nbr_elements++;
    while (child->parser_redirect_input[i])
    {
        if (!ft_strcmp(child->parser_redirect_input[i], "<<"))
        {
            if (here_doc(child->parser_redirect_input[i + 1], i, nbr_elements))
                return (1);
            if (i == nbr_elements - 2)
            {
                child->fd_in = open("heredoc", O_RDONLY);
                if (child->fd_in < 0)
                    return (perror_return("Error heredoc : "));
                exec->isheredoc = 1;
            }
        }
        i += 2;
    }
    return (0);
}

int	open_heredoc(t_child **child, t_exec *exec)
{
	int	i;

	i = 0;
	while (child[i])
	{
		if (child[i]->parser_redirect_input[0] != NULL)
		{
			if (get_heredoc(child[i], exec))
				return (1);
		}
		i++;
	}
	return (0);
}

int	executor (t_lex	*lex, t_child **child, t_exec *exec, t_env *env)
{
	int	i;

	i = 0;
	if (open_heredoc(child, exec))
		return (1);
	while (child[i])
	{
		if (command_path(child[i], env))
			return (1);
		if (processes(lex, child[i], exec, env))
			return (1);
		i++;
	}
	return (0);
}
