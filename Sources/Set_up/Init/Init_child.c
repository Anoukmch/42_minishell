#include "../../../includes/minishell.h"

static void	count_processes(t_lex *lex)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (lex->lexer && lex->lexer[i])
	{
		if (ft_strncmp(lex->lexer[i], "|", 2) == 0)
			c++;
		i++;
	}
	lex->no_processes = c + 1;
}

static void	init_cmds(t_lex *lex, t_child *child)
{
	child->no_cmd_opt = 0;
	child->input_counter = 0;
	child->output_counter = 0;
	while (lex->lexer[lex->iter]
		&& ft_strncmp(lex->lexer[lex->iter], "|", 2) != 0)
	{
		if (ft_strncmp(lex->lexer[lex->iter], "<", 2) == 0
			|| ft_strncmp(lex->lexer[lex->iter], "<<", 3) == 0)
		{
			child->input_counter += 2;
			lex->iter += 2;
		}
		else if (ft_strncmp(lex->lexer[lex->iter], ">", 2) == 0
			|| ft_strncmp(lex->lexer[lex->iter], ">>", 3) == 0)
		{
			child->output_counter += 2;
			lex->iter += 2;
		}
		else
		{
			child->no_cmd_opt++;
			lex->iter++;
		}
	}
	lex->iter++;
}

t_child	*init_single_child(t_lex *lex, t_child *child, int k)
{
	child = ft_calloc(1, sizeof(t_child));
	if (child == NULL)
		return (NULL);
	init_cmds(lex, child);
	child->parser_cmd
		= ft_calloc(child->no_cmd_opt + 1, sizeof(char *));
	child->parser_redirect_input
		= ft_calloc(child->input_counter + 1, sizeof(char *));
	child->parser_redirect_output
		= ft_calloc(child->output_counter + 1, sizeof(char *));
	if (child->parser_redirect_output == NULL
		|| child->parser_redirect_input == NULL
		|| child->parser_cmd == NULL)
		return (NULL);
	child->command = NULL;
	child->fd_in = -1;
	child->fd_out = -1;
	child->id = k;
	child->heredoc_quotes = 0;
	child->isbuiltin = false;
	child->heredoc_line = NULL;
	child->set_stdin_back = 0;
	child->file = -1;
	child->file_buff = ft_itoa(child->id);
	if (!child->file_buff)
		return (NULL);
	return (child);
}

t_child	**initialize_child(t_lex *lex)
{
	t_child	**child;
	int		k;

	k = 0;
	count_processes(lex);
	child = ft_calloc(lex->no_processes + 1, sizeof(t_child *));
	if (child == NULL)
		return (NULL);
	lex->iter = 0;
	while (k < lex->no_processes)
	{
		child[k] = init_single_child(lex, child[k], k);
		if (!child[k])
			return (NULL);
		k++;
	}
	child[lex->no_processes] = NULL;
	return (child);
}
