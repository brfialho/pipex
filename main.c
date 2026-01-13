/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:05:36 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/13 18:49:18 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_pipex	pipex;

	ft_bzero(&pipex, sizeof(t_pipex));
	parsing(&pipex, argc, argv);
	open_files(&pipex);
	create_childs(&pipex);
	kill_childs(&pipex);
	destroy_all(&pipex, CLEAN);
}

// void	print_each(void *content)
// {
// 	ft_split_print((char **)content);
// }

// void	close_pipes(t_pipex *pipex)
// {
// 	int	pipes;

// 	pipes = lst_size(*pipex->cmd) - 1;
// 	while (pipes--)
// 	{
// 		close(pipex->pipe[READ]);
// 		close(pipex->pipe[WRITE]);
// 	}
// }

// void	first_child(t_pipex *pipex, char *cmd, int i)
// {
// 	char	*bin;

// 	close(pipex->pipe[i][READ]);
// 	bin = ft_strjoin("/bin/", cmd);
// 	if (!bin)
// 		destroy_all(pipex, MEM);
// 	dup2(pipex->pipe[i][WRITE], 1);
// 	close(pipex->pipe[i][WRITE]);
// 	execv(bin, (char *[]){cmd, pipex->input.path, NULL});
// 	ft_printf("Command '%s' not found\n", cmd);
// 	free(bin);
// 	destroy_all(pipex, CLEAN);
// 	exit(1);
// }

// void	middle_child(t_pipex *pipex, char *cmd, int i)
// {
// 	char	*bin;
// 	char	*arg;

// 	close(pipex->pipe[i + 1][READ]);
// 	close(pipex->pipe[i][WRITE]);
// 	arg = read_from_pipe(pipex->pipe[i][READ]);
// 	close(pipex->pipe[i][READ]);
// 	bin = ft_strjoin("/bin/", cmd);
// 	if (!bin)
// 		destroy_all(pipex, MEM);
// 	dup2(pipex->pipe[i + 1][WRITE], 1);
// 	close(pipex->pipe[i + 1][WRITE]);
// 	execv(bin, (char *[]){cmd, arg, NULL});
// 	ft_printf("Command '%s' not found\n", cmd);
// 	free(bin);
// 	destroy_all(pipex, CLEAN);
// 	exit(1);
// }

// void	last_child(t_pipex *pipex, char *cmd, int i)
// {
// 	char	*bin;
// 	char	*arg;

// 	close(pipex->pipe[i][WRITE]);
// 	bin = ft_strjoin("/bin/", cmd);
// 	if (!bin)
// 		destroy_all(pipex, MEM);
// 	arg = read_from_pipe(pipex->pipe[i][READ]);	
// 	close(pipex->pipe[i][READ]);
// 	dup2(pipex->output.fd, 1);
// 	execv(bin, (char *[]){cmd, arg, NULL});
// 	ft_printf("Command '%s' not found\n", cmd);
// 	free(bin);
// 	destroy_all(pipex, CLEAN);
// 	exit(1);
// }

// void	create_pipes(t_pipex *pipex)
// {
// 	int	pipes;
// 	int	i;

// 	pipes = lst_size(*pipex->cmd) - 1;
// 	pipex->pipe = ft_calloc(pipes, sizeof(int [2]));
// 	if (!pipex->pipe)
// 		destroy_all(pipex, MEM);
// 	i = -1;
// 	while (++i < pipes)
// 		pipe(pipex->pipe[i]);
// }

// void	create_childs(t_pipex *pipex)
// {
// 	t_list	*lst;
// 	int		i;

// 	lst = *pipex->cmd;
// 	i = 0;
// 	if (!fork())
// 		first_child(pipex, lst->content, i);
// 	lst = lst->next;
// 	while (lst->next)
// 	{
// 		if (!fork())
// 			middle_child(pipex, lst->content, i);
// 		lst = lst->next;
// 	}
// 	if (!fork())
// 		last_child(pipex, lst->content, i);
// }