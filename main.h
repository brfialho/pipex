/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:07:45 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/07 21:58:12 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_file
{
	char	*path;
	int		fd;
}	t_file;

typedef struct s_pipex
{
	int		pid;
	int		fd[2];
	t_file	input;
	t_file	output;
	t_list	**cmd;
}	t_pipex;

typedef enum e_error
{
	CLEAN,
	INPUT_FILE,
	OPEN
}	t_error;

#endif