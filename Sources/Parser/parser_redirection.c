/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:01:43 by amechain          #+#    #+#             */
/*   Updated: 2022/11/07 10:43:59 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_redirection_table(t_lex *lex, t_child *child)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	lex = (void *)lex;
	while (lex->lexer[lex->counter] && ft_strcmp(lex->lexer[lex->counter], "|"))
	{
		if (!ft_strcmp(lex->lexer[lex->counter], "<") || !ft_strcmp(lex->lexer[lex->counter], "<<"))
		{
			child->parser_redirect_input[i++] = ft_substr(lex->lexer[lex->counter++], 0, 2);
			child->parser_redirect_input[i++] = ft_substr(lex->lexer[lex->counter], 0, ft_strlen(lex->lexer[lex->counter]));
			if (!child->parser_redirect_input[i - 1] || !child->parser_redirect_input[i - 2])
				errorexit("Allocation failed");
		}
		else if (!ft_strcmp(lex->lexer[lex->counter], ">") || !ft_strcmp(lex->lexer[lex->counter], ">>"))
		{
			child->parser_redirect_output[j++] = ft_substr(lex->lexer[lex->counter++], 0, 2);
			child->parser_redirect_output[j++] = ft_substr(lex->lexer[lex->counter], 0, ft_strlen(lex->lexer[lex->counter]));
			if (!child->parser_redirect_output[j - 1] || !child->parser_redirect_output[j - 2])
				errorexit("Allocation failed");
		}
		lex->counter++;
	}
	child->parser_redirect_input[i] = NULL;
	child->parser_redirect_output[j] = NULL;
}

// void	here_doc(char *limiter, int i, int nbr_elements)
// {
// 	int		file;
// 	char	*line;
// 	char	*temp;

// 	file = open("heredoc", O_CREAT | O_WRONLY
// 			| O_TRUNC, 0644);
// 	if (file < 0)
// 		errorexit("Open heredoc failed");
// 	temp = ft_strjoin(limiter, "\n");
// 	ft_printf("Heredoc>");
// 	line = get_next_line(STDIN_FILENO);
// 	if (!line)
// 		ft_printf("Get_next_line failed");
// 	while (ft_strncmp(line, temp, (ft_strlen(temp) + 1)))
// 	{
// 		if (i == nbr_elements - 2)
// 			ft_putstr_fd(line, file);
// 		free(line);
// 		ft_printf("Heredoc>");
// 		line = get_next_line(STDIN_FILENO);
// 		if (!line)
// 			errorexit("Get_next_line failed");
// 	}
// 	free(line);
// 	free(temp);
// 	close(file);
// }

void	check_redirection_table(char **parser_redirect_input, int i, int j)
{
	int	k;

	k = 0;
	if (ft_strcmp(parser_redirect_input[i], "<") && ft_strcmp(parser_redirect_input[i], "<<"))
		errorexit("Wrong redirection input");
	while(parser_redirect_input[j][k])
	{
		if (parser_redirect_input[j][k] == '|' || parser_redirect_input[j][k] == '&'
			|| parser_redirect_input[j][k] == ';' || parser_redirect_input[j][k] == '('
			|| parser_redirect_input[j][k] == ')' || parser_redirect_input[j][k] == '<'
			|| parser_redirect_input[j][k] == '>' || parser_redirect_input[j][k] == '$')
			errorexit("Wrong token filename");
		k++;
	}
}

// void	get_outfile(t_child *child)
// {
// 	int	i;
// 	int nbr_elements;

// 	i = 0;
// 	nbr_elements = 0;
// 	while (child->parser_redirect_output[nbr_elements])
// 		nbr_elements++;
// 	while (child->parser_redirect_output[i])
// 	{
// 		//check_redirection_table(child->parser_redirect_output, i, i + 1);
// 		if (!ft_strcmp(child->parser_redirect_output[i], ">"))
// 		{
// 			child->fd_out = open(child->parser_redirect_output[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 			if (child->fd_out < 0)
// 				errorexit("Open outfile failed");
// 			if (i < nbr_elements - 2)
// 				close(child->fd_out);
// 		}
// 		else if (!ft_strcmp(child->parser_redirect_output[i], "<<"))
// 		{
// 			child->fd_out = open(child->parser_redirect_output[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (child->fd_out < 0)
// 				errorexit("Open outfile failed");
// 			if (i < nbr_elements - 2)
// 				close(child->fd_out);
// 		}
// 		i += 2;
// 	}
// }

// void	get_infile(t_child *child)
// {
// 	int	i;
// 	int nbr_elements;

// 	i = 0;
// 	nbr_elements = 0;
// 	while (child->parser_redirect_input[nbr_elements])
// 		nbr_elements++;
// 	while (child->parser_redirect_input[i])
// 	{
// 		//check_redirection_table(child->parser_redirect_input, i, i + 1);
// 		if (!ft_strcmp(child->parser_redirect_input[i], "<"))
// 		{
// 			child->fd_in = open(child->parser_redirect_input[i + 1], O_RDONLY);
// 			if (child->fd_in < 0)
// 				errorexit("Open infile failed");
// 			if (i < nbr_elements - 2)
// 				close(child->fd_in);
// 		}
// 		else if (!ft_strcmp(child->parser_redirect_input[i], "<<"))
// 		{
// 			here_doc(child->parser_redirect_input[i + 1], i, nbr_elements);
// 			if (i == nbr_elements - 2)
// 			{
// 				child->fd_in = open("heredoc", O_RDONLY);
// 				if (child->fd_in < 0)
// 					errorexit("Open infile heredoc failed");
// 			}
// 		}
// 		i += 2;
// 	}
// }

void	parser_redirection(t_lex *lex, t_child **child)
{
	int	i;

	i = 0;
	lex->counter = 0;
	while (child[i])
	{
		fill_redirection_table(lex, child[i]);
		i++;
		lex->counter++;
	}
}

