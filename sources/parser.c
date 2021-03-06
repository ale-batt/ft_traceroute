/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 12:31:35 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/14 16:25:38 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static void	opt_first_ttl(t_env *env, char *str_ttl)
{
	env->ttl = ft_atoi(str_ttl);
	if (env->ttl <= 0)
	{
		printf("ft_traceroute: first ttl must be > 0\n");
		exit(EXIT_FAILURE);
	}
}

static void	opt_max_ttl(t_env *env, char *str_max_ttl)
{
	env->max_ttl = ft_atoi(str_max_ttl);
	if (env->max_ttl <= 0)
	{
		printf("ft_traceroute: max ttl must be > 0\n");
		exit(EXIT_FAILURE);
	}
}

static void	opt_nqueries(t_env *env, char *str_nqueries)
{
	env->nqueries = ft_atoi(str_nqueries);
	if (env->nqueries <= 0)
	{
		printf("ft_traceroute: nqueries must be > 0\n");
		exit(EXIT_FAILURE);
	}
}

static void	opt_tos(t_env *env, char *str_tos)
{
	env->tos = ft_atoi(str_tos);
	if (env->tos < 0 || env->tos > 255)
	{
		printf("ft_traceroute: tos must be > 0 && < 255\n");
		exit(EXIT_FAILURE);
	}
}

int			parse(t_env *env, char **av)
{
	int		y;

	y = 0;
	while (av[y])
	{
		if (ft_strequ(av[y], "-m") || ft_strequ(av[y], "-h"))
			opt_max_ttl(env, av[++y]);
		else if (ft_strequ(av[y], "-f"))
			opt_first_ttl(env, av[++y]);
		else if (ft_strequ(av[y], "-q"))
			opt_nqueries(env, av[++y]);
		else if (ft_strequ(av[y], "-p"))
			env->port = ft_atoi(av[++y]);
		else if (ft_strequ(av[y], "-t"))
			opt_tos(env, av[++y]);
		else
		{
			env->hostip = hostname_to_ip(av[y]);
			if (env->hostip != NULL)
			{
				env->hostname = ft_strdup(av[y]);
				break ;
			}
		}
		y++;
	}
	if (env->hostip == NULL)
		return (-1);
	return (1);
}
