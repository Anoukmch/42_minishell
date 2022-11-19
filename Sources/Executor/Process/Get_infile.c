#include "../../../includes/minishell.h"

int	get_infile(t_child *child)
{
	int	i;
	int	nbr_elements;
	int	tmp;

	i = 0;
	nbr_elements = 0;
	if (child->parser_redirect_input[0] == NULL)
		return (0);
	while (child->parser_redirect_input[nbr_elements])
		nbr_elements++;
	while (child->parser_redirect_input[i])
	{
		if (!ft_strcmp(child->parser_redirect_input[i], "<"))
		{
			tmp = open(child->parser_redirect_input[i + 1], O_RDONLY);
			if (tmp < 0)
				return (perror_return_status("Error infile", 1));
			if (i < nbr_elements - 2)
				close(tmp);
			else
				child->fd_in = tmp;
		}
		i += 2;
	}
	return (0);
}
