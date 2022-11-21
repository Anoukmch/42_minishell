#include "../../includes/minishell.h"

char	*ft_strapp(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	free(s1);
	return (temp);
}
