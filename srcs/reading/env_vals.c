/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 03:57:10 by tmoska            #+#    #+#             */
/*   Updated: 2017/04/05 20:19:40 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	within_single_q(char *str)
{
	int	i;
	int	pos;
	int	s_q_l;
	int	s_q_r;
	int	str_len;

	i = 0;
	pos = 0;
	s_q_l = 0;
	s_q_r = 0;
	str_len = ft_strlen(str);
	while (str[pos] != '$')
		pos++;
	while (i < pos)
		str[i++] == '\'' ? s_q_l++ : (0);
	while (i < str_len)
		str[i++] == '\'' ? s_q_r++ : (0);
	if (s_q_l == 0 && s_q_r == 0)
		return (0);
	return ((s_q_l == s_q_r) ? 1 : 0);
}

static char	*dup_env_val(char *pt)
{
	size_t	sz;

	sz = 1;
	if (pt[sz] <= '9' && pt[sz] >= '1')
		return (NULL);
	while (((pt[sz] >= 'A' && pt[sz] <= 'Z') || pt[sz] == '_' ||
			(pt[sz] >= '1' && pt[sz] <= '9')))
		sz++;
	return (ft_strndup(pt, sz));
}

static void	join_words_to_buff(t_shell **shell, char **words)
{
	char	*tmp;
	int		i;

	i = 1;
	ft_strdel(&(*shell)->buff);
	(*shell)->buff = ft_strdup(words[0]);
	while (words[i])
	{
		tmp = (*shell)->buff;
		(*shell)->buff = ft_str3join((*shell)->buff, " ", words[i]);
		ft_strdel(&tmp);
		i++;
	}
}

int			status_env(t_shell **shell, char ***words, int i)
{
	char	*tmp;

	if (ft_strstr((*words)[i], "$?"))
	{
		tmp = ft_itoa((*shell)->ret);
		ft_str_replace(&(*words)[i], "$?", tmp, 1);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

int			replace_env_vals(t_shell **shell)
{
	char	**words;
	char	*pt;
	char	*env_val;
	char	*tmp;
	int		i;

	i = 0;
	words = ft_strsplit((*shell)->buff, ' ');
	while (words[i])
	{
		if (!within_single_q(words[i]) && (pt = ft_strchr(words[i], '$')))
		{
			if (status_env(shell, &words, i))
				continue ;
			if (!(tmp = dup_env_val(pt)))
				return (-1);
			if ((env_val = get_env_val(shell, &(tmp[1]))))
				ft_str_replace(&words[i], tmp, env_val, 1);
			ft_strdel(&tmp);
		}
		i++;
	}
	join_words_to_buff(shell, words);
	ft_str2del(&words);
	return (0);
}
