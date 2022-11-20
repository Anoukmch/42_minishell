#include "../../includes/minishell.h"

int	split_parserline(t_lex *lex, t_child *child, int *j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	printf("TEST\n");
	// child->parser_cmd[*j] = ft_strdup(lex->lexer[lex->iter] + &ft_strchr(lex->lexer[lex->iter], -3));
	// child->parser_cmd[*j] = ft_strdup(lex->lexer[lex->iter] - ft_strchr())
	// while (lex->lexer[lex->iter][i] && lex->lexer[lex->iter][i] != -3)
	// {
	// 	printf("LEXER: %c\n", lex->lexer[lex->iter][i]);
	// 	child->parser_cmd[*j][k] = lex->lexer[lex->iter][i];
	// 		k++;
	// 		i++;
	// }
	return (0);
}

void	ft_split_ovr(char **p1, char **p2)
{
	int	i;

	i = 0;
	while (p2 && p2[i])
	{
		printf("IIIIIII: %i\n", i);
		free(p1[i]);
		p1[i] = p2[i];
		printf("p2: %s\n", p2[i]);
		i++;
	}
}

int allocate_parse_cmd(t_lex *lex, t_child *child, int *j, int *count)
{
	printf("NEW ALLOCATION\n");
	printf("STRING: %s\n", (lex->lexer[lex->iter]));
	child->parser_cmd = ft_calloc(child->no_cmd_opt + (*count) + 1, sizeof(char *));
	if (!child->parser_cmd)
		return (1);
	if (split_parserline(lex, child, j))
		return (1);
	return (0);
}

int check_first_command(t_lex *lex, t_child *child, int *j)
{
	char	quote;
	int		count;
	int		i;

	quote = '\0';
	count = 0;
	i = 0;
	while (lex->lexer[lex->iter][i])
	{
		skipquotes(&quote, lex->lexer[lex->iter][i]);
		if ((quote == '\0' && lex->lexer[lex->iter][i] == ' '))
		{
			lex->lexer[lex->iter][i] = -3;
			count++;
		}
		i++;
	}
	if (count == 0)
		return (2);
	else if (allocate_parse_cmd(lex, child, j, &count))
		return (1);
	return (0);
}

int	commands(t_lex *lex, t_child *child, int j)
{
	while (lex->lexer[lex->iter]
		&& ft_strcmp(lex->lexer[lex->iter], "|"))
	{
		if (!ft_strcmp(lex->lexer[lex->iter], "<")
			|| !ft_strcmp(lex->lexer[lex->iter], "<<")
			|| !ft_strcmp(lex->lexer[lex->iter], ">")
			|| !ft_strcmp(lex->lexer[lex->iter], ">>"))
			lex->iter += 2;
		else
		{
			// if (j == 0)
			// {
			// 	z = check_first_command(lex, child, &j);
			// 	if (z == 1)
			// 		return (1);
			// 	printf("j: %d\n", j);
			// 	// j++;
			// }
			// if (j != 0 || z == 2)
			// {
				child->parser_cmd[j] = ft_strdup(lex->lexer[lex->iter]);
				if (!child->parser_cmd[j])
					return (1);
				if (mark_quotes_cmds_and_outdir(child->parser_cmd[j]))
					return (1);	
				child->parser_cmd[j] = delete_quotes_cmds_and_outdir
					(child->parser_cmd[j]);
			// }
			j++;
			lex->iter++;
		}
	}
	child->parser_cmd[j] = NULL;
	return (0);
}

int	parse_commands(t_lex *lex, t_child **child)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	lex->iter = 0;
	while (k < lex->no_processes)
	{
		if (commands(lex, child[k], j))
			return (1);
		lex->iter++;
		k++;
	}
	return (0);
}
