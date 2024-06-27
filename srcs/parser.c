/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:28:30 by kammi             #+#    #+#             */
/*   Updated: 2024/06/27 14:44:43 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	while (i < ac)
	{
		j = 0;
		len = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]) || len > 10)
			{
				ft_putstr_fd("Error: wrong arguments\n", 2);
				return (1);
			}
			j++;
			len++;
		}
		i++;
	}
	return (0);
}

int	parser(int ac, char **av, t_table *table)
{
	int	err;

	err = 0;
	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	if (check_args(ac, av))
		return (1);
	table->nbr_philos = ft_atol(av[1], &err);
	table->time_to_die = ft_atol(av[2], &err);
	table->time_to_eat = ft_atol(av[3], &err);
	table->time_to_sleep = ft_atol(av[4], &err);
	table->start_time = get_time() + table->nbr_philos * 10;
	if (ac == 6)
		table->nbr_must_eat = ft_atol(av[5], &err);
	else
		table->nbr_must_eat = 0;
	if (err)
		return (ft_putstr_fd("Error: wrong arguments\n", 2), 1);
	if (table->nbr_philos < 1 || table->time_to_die < 60
		|| table->time_to_eat < 60 || table->time_to_sleep < 60
		|| (ac == 6 && table->nbr_must_eat < 1))
		return (ft_putstr_fd("Error: wrong arguments\n", 2), 1);
	return (0);
}
