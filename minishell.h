/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoizmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 22:29:23 by zoizmer           #+#    #+#             */
/*   Updated: 2021/12/05 22:29:25 by zoizmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include <unistd.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
//mine
#include <sys/stat.h>
#include <fcntl.h>
//endmine;

typedef struct s_cmd // commands
{
	char			*cmd;
	char			**args;
	struct s_red	*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_red // redirections;
{
	char			type;
	char			*arg;// is it the file name
	struct s_red	*next;
}	t_red;

typedef struct s_node {// envirement variables i think;
	char			*name;
	char			*val;
	struct s_node	*next;
}	t_node;

typedef struct { // to replace envirement variables with their values;
	int		i;
	char	*ret;
	char	*name;
	char	*val;
	char	*val2;
}	s_rp;

typedef struct s_fr {
	void		*name;
	struct s_fr	*next;
}	t_fr;

int		scan(char *str);
int		parse_and_exec(char *buf, t_node	*node,char **env/*i added this argument*/);
t_cmd	*alloc_cmd_s(void);
t_red	*alloc_red_s(void);
int		end_of_delimiter(char *str);
void	subarg(int	*r, int i, char *str, t_red *red);
int		sizelen(char	*str, int	ret, int	i, int	trig);
char	**splitargs(char	*str);
void	data_proc(t_cmd	*strct, t_node	*node);
char	*env_val(char	*name, t_node	*node);
void	free_null(void	*buff);
void	free_strct(t_cmd	*strct, t_red	*tmp, t_red	*tmp2, t_cmd	*tmp3);
void	free_node(t_node	*node);
char	*get_arg(char	*str, int	*r);
char	**copy_env(char	**env);
void	test_add(t_node	**head, char	*name, char	*val);
void	init_struct(char	**envp, t_node	**head);
char	*ft_strjoin1(char	*s1, char const	*s2);
void	*ft_memcpy1(void *dest, const void *src, size_t n);
char	*get_name(char	*str);
void	print_strct(t_cmd	*strct);
void	rm_quotes(t_cmd *srtct);
void	protection(t_cmd *node);
int		sizeoftab(char	**tab);
void	get_line(t_node *node,char **env/*i added this argument*/);
//mine;
void ft_excution(t_cmd *strct, t_node *node,char **env);
int simple_non_builtin_cmd(t_cmd *strct);

#endif