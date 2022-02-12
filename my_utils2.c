#include "minishell.h"

// #include "./libft/libft.h"
// #include <stdio.h>
// #include <unistd.h>
char	*add_char_beggin(char *str, char c)
{
	char	*tmp;
	char	*join;

	tmp = malloc(sizeof(char) * 2);
	tmp[0] = c;
	tmp[1] = '\0';
	join = ft_strjoin (tmp, str);
	free(tmp);
	return (join);
}

char	*add_char_end(char *str, char c)
{
	char	*tmp;
	char	*join;

	tmp = malloc(sizeof(char) * 2);
	tmp[0] = c;
	tmp[1] = '\0';
	join = ft_strjoin(str, tmp);
	free(tmp);
	return (join);
}

int	node_exist(char *args, t_node *node, int i, t_node *new_node)
{
	if (!ft_strcmp(node->name, new_node->name))
	{
		if (args[i] == '=')
		{
			new_node->val = add_char_beggin(new_node->val, '"');
			new_node->val = add_char_end(new_node->val, '"');
			node->val = new_node->val;
			return (1);
		}
		else
			return (1);
	}
	else
		return (0);
}

void	unset_errors(char **args)
{
	int	i;
	int	j;

	i = 1;// it may be 0;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isalpha(args[i][j]))
			{
				printf("unset: `%s': not a valid identifier\n", args[i]);
				//return(0); should be uncommented later;
			}
			j++;
		}
		i++;
		// end of check_error;
	}
}
