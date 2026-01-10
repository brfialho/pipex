/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:05:36 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/10 18:52:20 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	destroy_all(t_pipex *pipex, t_error error)
{
	if (error == INPUT_FILE)
		ft_printf("%s: %s: No such file or directory\n", ((t_list *)(*pipex->cmd)->content), pipex->input.path);
	if (error == OPEN)
		ft_printf("Could not open files\n");
	if (error == MEM)
		ft_printf("Memory error\n");
	if (pipex->pipe)
		free(pipex->pipe);
	lst_del_all(pipex->cmd, NULL);
	free(pipex->cmd);
	exit(1);
}

void	parsing(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	if (argc < 5)
		exit(1);
	pipex->cmd = ft_calloc(1, sizeof(t_list **));
	if (!pipex->cmd)
		exit(2);
	i = 1;
	while (++i < argc - 1)
		lst_add_end(pipex->cmd, lst_new_node(argv[i]));
	pipex->input.path = argv[1];
	pipex->output.path = argv[argc - 1];
}

void	open_files(t_pipex *pipex)
{
	if (access(pipex->input.path, F_OK))
		destroy_all(pipex, INPUT_FILE);
	pipex->input.fd = open(pipex->input.path, O_RDONLY);
	if (pipex->input.fd == -1)
		destroy_all(pipex, OPEN);
	if (access(pipex->output.path, F_OK))
		pipex->output.fd = open(pipex->output.path, O_CREAT | O_WRONLY, 0666);
	else
		pipex->output.fd = open(pipex->output.path, O_WRONLY);
	if (pipex->output.fd == -1)
		close(pipex->output.fd), destroy_all(pipex, OPEN);
}

void	child_labour(t_pipex *pipex, char *cmd)
{
	char	*bin;

	close(pipex->pipe[READ]);
	bin = ft_strjoin("/bin/", cmd);
	if (!bin)
		destroy_all(pipex, MEM);
	dup2(pipex->pipe[WRITE], 1);
	execv(bin, (char *[]){cmd, NULL});
	close(pipex->pipe[WRITE]);
	ft_printf("Command '%s' not found\n", cmd);
	free(bin);
	destroy_all(pipex, CLEAN);
	exit(1);
}

void	first_child(t_pipex *pipex, char *cmd, int i)
{
	char	*bin;

	close(pipex->pipe[i][READ]);
	bin = ft_strjoin("/bin/", cmd);
	if (!bin)
		destroy_all(pipex, MEM);
	dup2(pipex->pipe[i][WRITE], 1);
	close(pipex->pipe[i][WRITE]);
	execv(bin, (char *[]){cmd, pipex->input.path, NULL});
	ft_printf("Command '%s' not found\n", cmd);
	free(bin);
	destroy_all(pipex, CLEAN);
	exit(1);
}

void	middle_child(t_pipex *pipex, char *cmd, int i)
{
	char	*bin;
	char	*arg;

	close(pipex->pipe[i + 1][READ]);
	close(pipex->pipe[i][WRITE]);
	arg = read_from_pipe();
	close(pipex->pipe[i][READ]);
	bin = ft_strjoin("/bin/", cmd);
	if (!bin)
		destroy_all(pipex, MEM);
	dup2(pipex->pipe[i + 1][WRITE], 1);
	close(pipex->pipe[i + 1][WRITE]);
	execv(bin, (char *[]){cmd, arg, NULL});
	ft_printf("Command '%s' not found\n", cmd);
	free(bin);
	destroy_all(pipex, CLEAN);
	exit(1);
}

void	last_child(t_pipex *pipex, char *cmd, int i)
{
	char	*bin;

	close(pipex->pipe[i][READ]);
	bin = ft_strjoin("/bin/", cmd);
	if (!bin)
		destroy_all(pipex, MEM);
	dup2(pipex->pipe[i][WRITE], 1);
	close(pipex->pipe[i][WRITE]);
	execv(bin, (char *[]){cmd, pipex->input.path, NULL});
	ft_printf("Command '%s' not found\n", cmd);
	free(bin);
	destroy_all(pipex, CLEAN);
	exit(1);
}
// void	read_to_file(t_pipex *pipex)
// {
// 	int 	b_read;
// 	char	c;

// 	while ((b_read = read(pipex->pipe[0], &c, 1)))
// 		write(pipex->output.fd, &c, 1);
// }

void	create_pipes(t_pipex *pipex)
{
	int	pipes;
	int	i;

	pipes = lst_size(pipex->cmd) - 1;
	pipex->pipe = ft_calloc(pipes, sizeof(int [2]));
	if (!pipex->pipe)
		destroy_all(pipex, MEM);
	i = -1;
	while (++i < pipes)
		pipe(pipex->pipe[i]);
}

void	create_childs(t_pipex *pipex)
{
	t_list	*lst;
	int		i;

	lst = *pipex->cmd;
	i = 0;
	if (!fork())
		first_child(pipex, lst->content, i);
	while (lst->next)
	{
		if (!fork())
			middle_child(pipex, lst->content, i);
		lst = lst->next;
	}
	if (!fork())
		last_child(pipex, lst->content, i);
}

void	close_pipes(t_pipex *pipex)
{
	int	pipes;

	pipes = lst_size(pipex->cmd) - 1;
	while (pipes--)
	{
		close(pipex->pipe[pipes][READ]);
		close(pipex->pipe[pipes][WRITE]);
	}
}

int	main(int argc, char **argv)
{
	t_pipex	pipex;

	ft_bzero(&pipex, sizeof(t_pipex));
	parsing(&pipex, argc, argv);
	open_files(&pipex);
	create_pipes(&pipex);
	create_childs(&pipex);
	close_pipes(&pipex);
	close(pipex.input.fd);
	close(pipex.output.fd);
	destroy_all(&pipex, CLEAN);
}
