#include "../../../includes/minishell.h"

int	command_echo(t_child *child)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (child->parser_cmd[i] != NULL
		&& !ft_strcmp(child->parser_cmd[i], "-n"))
	{
		newline = false;
		i++;
	}
	while (child->parser_cmd[i])
	{
		if (!ft_strcmp(child->parser_cmd[1], "~"))
			ft_printf("%s", getenv("HOME"));
		else
			ft_printf("%s", child->parser_cmd[i]);
		if (child->parser_cmd[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (newline == true)
		ft_printf("\n");
	return (0);
}
