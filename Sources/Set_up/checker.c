

#include "../../includes/minishell.h"

// CHECKING LEXER
void	print_lexer(t_lex *lex)
{
	int	i;

	i = 0;
	lex->iter = 0;
	printf("\n*** LEXER ***\n");
	while (lex->lexer[lex->iter])
	{
		printf("%s\n", lex->lexer[lex->iter]);
		lex->iter++;
	}
	printf("%s\n", lex->lexer[lex->iter]);
}

// CHECKING PARSER
void	print_parser(t_child **child)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	printf("\n*** PARSER ***\n");
	while (child[k])
	{
		i = 0;
		while (i < child[k]->no_cmd_opt)
			printf("parser cmd for child %d : %s\n",
				k, child[k]->parser_cmd[i++]);
		i = 0;
		if (!child[k]->input_counter)
			printf("No redirection input\n");
		while (i < child[k]->input_counter)
			printf("parser input for child %d : %s\n",
				k, child[k]->parser_redirect_input[i++]);
		i = 0;
		if (!child[k]->output_counter)
			printf("No redirection output\n");
		while (i < child[k]->output_counter)
			printf("parser output for child %d : %s\n",
				k, child[k]->parser_redirect_output[i++]);
		k++;
	}
	printf("\n");
}
