/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:23:20 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 10:45:56 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_flag_action(char *path_env, char *old_path_env, int flag)
{
	if (flag == 1)
	{
		if (ft_check_oldpwd())
			ft_export_add_check(old_path_env);
		ft_export_add_check(path_env);
	}
	if (flag == 0)
	{
		if (ft_check_oldpwd() == 2)
			ft_export_add_check("OLDPWD=");
		else if (ft_check_oldpwd() == 1)
			ft_export_add_check(old_path_env);
	}
}

void	ft_change_pwd(char *path, char *old_path)
{
	int		i;
	int		flag;
	char	*old_path_env;
	char	*path_env;

	i = 0;
	flag = 0;
	old_path_env = ft_join("OLDPWD=", old_path, 0);
	path_env = ft_join("PWD=", path, 0);
	while (g_o.env[i])
	{
		if (!ft_strncmp(g_o.env[i], "PWD=", 4))
		{
			flag = 1;
			break ;
		}
		i++;
	}
	ft_flag_action(path_env, old_path_env, flag);
	free(old_path);
	free(path);
	free(old_path_env);
	free(path_env);
}

int	ft_find_home(void)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	while (g_o.env[++i])
	{
		if (!ft_strncmp(g_o.env[i], "HOME=", 5))
		{
			flag = 1;
			break ;
		}
	}
	if (flag == 0)
	{
		printf("$: cd: HOME not set\n");
		g_o.ex_code = 1;
		return (-1);
	}
	return (i);
}

void	ft_return_home(void)
{
	int		i;
	int		flag;
	char	*path;
	char	**home;
	char	*old_path;

	i = 0;
	flag = 0;
	old_path = NULL;
	i = ft_find_home();
	if (i < 0)
		return ;
	home = ft_split(g_o.env[i], '=');
	path = ft_strdup(home[1]);
	old_path = getcwd(old_path, 1000);
	if (chdir(home[1]) == -1)
	{
		printf("$: cd: %s: No such file or directory\n", home[1]);
		ft_free_mass(home);
		free(old_path);
		g_o.ex_code = 1;
		return ;
	}
	ft_free_mass(home);
	ft_change_pwd(path, old_path);
}

void	ft_cd(t_lst *tmp)
{
	char	*new_path;
	char	*old_path;

	old_path = NULL;
	new_path = NULL;
	if (!tmp->execve[1])
		return (ft_return_home());
	old_path = getcwd(old_path, 1000);
	if (chdir(tmp->execve[1]) == -1)
	{
		printf("$: cd: %s: No such file or directory\n",
			tmp->execve[1]);
		free(old_path);
		g_o.ex_code = 1;
		return ;
	}
	new_path = getcwd(new_path, 1000);
	ft_change_pwd(new_path, old_path);
	return ;
}
