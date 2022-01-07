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
	join = ft_strjoin(tmp,str);
	free(tmp);
	return(join);
}

char *add_char_end(char *str, char c)
{
	char	*tmp;
	char	*join;

	tmp = malloc(sizeof(char) * 2);
	tmp[0] = c;
	tmp[1] = '\0';
	join = ft_strjoin(str, tmp);
	free(tmp);
	return(join);
}

// int main()
// {
// 	char c = '"';
// 	char *str = "rachid";

// 	printf("%s\n",add_char_beggin(str,c));
// 	printf("%s\n",add_char_end(str,c));
// 	return(0);
// }