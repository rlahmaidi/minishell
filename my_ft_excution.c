 // if (simple_non_builtin_cmd())
// 	execute_non_builtin();
// while (strct->next)
// {
// 	int fd[2];
// 	pipe(fd);

// 	int id = fork();     KHAMISS;
// 	if (id == 0)
// 	{
// 		dup2(); //
// 		ft_redirection();
// 		check_builtin(); // if (cmd == echo) echo(args)  || cmd == ...)
// 		non_builtin(); //execve
// 	}
// 	final_cmd();
// 	strct = strct->next;

#include "minishell.h"

int non_builtin_cmd(t_cmd *strct)
{
	if (!ft_strncmp(strct->cmd, "exit", 4) || !ft_strncmp(strct->cmd, "export", 6) || !ft_strncmp(strct->cmd, "env", 3) || !ft_strncmp(strct->cmd, "pwd", 3) ||
		!ft_strncmp(strct->cmd, "cd", 2) || !ft_strncmp(strct->cmd, "unset", 5) ||
		!ft_strncmp(strct->cmd, "echo", 4))
				return (0);
	else
		return (1);
}

void redirection_handler(t_cmd *strct)
{
	t_red *tmp;
	int fd_out;
	int fd_in;

	tmp = strct->redirections;
	fd_in = -1;
	fd_out = -1;
	while (strct->redirections != NULL)
	{
		if (strct->redirections->type == 'o')
			fd_out = open(strct->redirections->arg, O_CREAT | O_RDWR | O_TRUNC);
		if (strct->redirections->type == 'a')
			fd_out = open(strct->redirections->arg, O_CREAT | O_RDWR | O_APPEND);
		if (strct->redirections->type == 'i')
		{
			fd_in = open(strct->redirections->arg, O_RDONLY);
			if (fd_in == -1)
				printf("%s :no such file or derictory", strct->redirections->arg);
		}
		if (strct->redirections->type == 'h')
		{
			fd_in = open(strct->redirections->arg, O_RDONLY); // it won't be treated  like this;
			if (fd_in == -1)
				printf("%s :no such file or derictory", strct->redirections->arg);
		}
		tmp = tmp->next;
	}
	if (fd_out != -1)
		dup2(1, fd_out);
	else
		close(fd_out); // is there any file descriptor -1 so that we need to close it;
	if (fd_in != -1)
		dup2(0, fd_in);
	else
		close(fd_in);
}

void builtins(t_cmd *strct, t_node *node)
{
	char *builtins_names[7] = {"cd", "pwd", "env", "export", "unset", "echo", "exit"}; // norme
	int (*builtins_functions[7])(char **, t_node *) = {&my_cd, &my_pwd, &my_env, &my_export, &my_unset, &my_echo, &my_exit};
	int i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(builtins_names[i], strct->args[0]))
		{
			builtins_functions[i](strct->args, node);
		}
		// printf("%s\n", builtins_names[i]);
		i++;
	}
}

void excute_last_command(t_cmd *strct,t_node *env)
{
	//the output will be in the standard output,not the pipe
	// we don't need to fork;
	int pid = fork();
	if (pid == 0)
	{

	//redirection_handler(strct);

	if (non_builtin_cmd(strct)) // && strct->next != NULL)
	{
		printf("%s\n",ft_get_path(strct->args[0], env));
		execve(ft_get_path(strct->args[0], env), strct->args, env_tmp);//khames add it and
		printf("command not found\n");
		//printf("test\n");	 // to change NULL into char **env			// and i think it = node;
		// close(fd[1]);
		exit(0); // it's not allowed but we should exit somehow;
	}
	else
	{
		builtins(strct, env);
		// close(fd[1]);
		exit(0);// somehow;
	}
	}
	waitpid(pid,NULL, 0);
}

char *ft_get_path(char *bin, t_node *env)
{
	char **bins;
	char *path;
	struct stat sb;

	while(env)
	{
		if(!ft_strcmp(env->name, "PATH"))
			break;
		env = env->next;
	}
	bins = ft_split(env->val, ':');
	while(*bins)
	{
		path = ft_strjoin(*bins, "/");
		path = ft_strjoin(path,bin);
		if (!stat(path,&sb))
			return (path);
		bins++;
		free(path);
	}
	return (bin);
}

int ft_excution(t_cmd *strct, t_node *node)
{
	int pid;
	int fd[2];
	int f;

	f = -1;
	// write(2,"dsadwasd\n",10);
	if (!non_builtin_cmd(strct) && strct->next == NULL)
	{
		redirection_handler(strct);
		builtins(strct, node);
		return 1;
		//execve(strct->cmd, strct->args, env);
	}
	while (strct->next != NULL)
	{
		char *p;
		p = ft_get_path(strct->args[0], node);
		write(2,p,ft_strlen(p));
		printf("%s\n",ft_get_path(strct->args[0], node));
		redirection_handler(strct);
		if (pipe(fd) < 0)
			return (1);
		if ((pid = fork()) < 0)
			return (1);
		else if (pid == 0)
		{
			close(fd[0]);
			if (strct->next != NULL)
				dup2(1, fd[1]);
			if (f != -1)
				dup2(0, f);
			if (non_builtin_cmd(strct) && strct->next != NULL)
			{
				execve(ft_get_path(strct->args[0], node), strct->args, env_tmp); //should i search for the path of the command; also change the NULL to char **env
				close(fd[1]);
				//exit(0); // it's not allowed but we should exit somehow;
			}
			else
			{
				
				builtins(strct, node);
				close(fd[1]);
				exit(1);
				//exit somehow;
			}
			// if ctr+c or ctr+d we should end the procces somehow;
		}
		else
		{
			close(fd[1]);
			f = fd[0];
			close(fd[0]);// but we should wait for the child to end
						// i think;
		}
		strct = strct->next;
	}
	excute_last_command(strct, node);
	return (0);
}

// while(cmd)
// {
// 	int fd[2];
// 	int f = -1;
// 	pipe(fd);
// 	fork;
// 	if(pid == 0)
// 	{
// 		if(ila makanch how akhir comd)               // mastapha;
// 			dup2(fd[1],1);
// 		if (f != -1)
// 			dup2(f, 0);
// 		close(fd[0]);
// 		exuction;
// 	}
// 	else
// 	{
// 	f = fd[0];
// 	close(fd[1]);
// 	}
// }