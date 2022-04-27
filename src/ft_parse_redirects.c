/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redirects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:19:02 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 13:49:33 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_parse(t_lst *o)
{
	int	i;

	i = -1;
	while (o->str[++i])
	{
		if (o->str[i] == '\'')
				o->str = ft_parse_quotes(o, &i, '\'');
		else if (o->str[i] == '"')
		{
			o->flag_meta = 1;
			o->str = ft_parse_quotes(o, &i, '"');
		}
		else if (o->str[i] == '$'
			&& (ft_isalnum(o->str[i + 1]) || o->str[i + 1] == '?'))
				o->str = ft_parse_dollar(o->str, &i);
	}
	o->flag_meta = 0;
}

int	ft_check_syntax(t_lst *o)
{
	if (!o->next)
		return (1);
	if (o->next->str[0] == '|' || o->next->str[0] == '<'
		|| o->next->str[0] == '>')
		return (1);
	return (0);
}

char	*ft_parse_lite(t_lst *o, int flag, int flag2)
{
	int		i;

	i = 0;
	if (ft_check_syntax(o))
		return (write(2, "syntax error\n", 13), ft_free_all(), NULL);
	ft_check_parse(o->next);
	if (flag == 1)
	{
		ft_heredoc(o->next);
		ft_check_heredoc(o);
	}
	else if (flag == 2)
	{
		o->pipe_flag = 1;
		ft_put_list(0);
		ft_put_final_args();
		o->pipe_flag = 0;
	}
	else if (ft_open_file(o->next, flag2))
	{
		g_o.ex_code = 1;
		return (write(2, "error open\n", 11), ft_free_all(), NULL);
	}
	return (free(o->str), NULL);
}

char	*ft_parse_redirect(t_lst *o, int flag, int flag2)
{
	if ((g_o.count > 1 && ft_strlen(o->str) == 1)
		|| (g_o.count > 1 && ft_strlen(o->str) == 2 && (o->str[1] == '<'
				|| o->str[1] == '>')))
		return (ft_parse_lite(o, flag, flag2));
	return (write(2, "syntax error\n", 13), ft_free_all(), NULL);
}

char	*ft_redirects(t_lst *o, int *j)
{
	if (o->str[*j] == '<' && o->str[*j + 1] == '<')
		o->str = ft_parse_redirect(o, 1, 0);
	else if (o->str[*j] == '<')
		o->str = ft_parse_redirect(o, 0, 1);
	else if (o->str[*j] == '>' && o->str[*j + 1] == '>')
		o->str = ft_parse_redirect(o, 0, 3);
	else if (o->str[*j] == '>')
		o->str = ft_parse_redirect(o, 0, 2);
	return (o->str);
}
