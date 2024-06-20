/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:28:30 by kammi             #+#    #+#             */
/*   Updated: 2024/06/18 16:42:53 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				ft_putstr_fd("Error: wrong arguments\n", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parser(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return (1);
	}
	if (check_args(ac, av))
		return (1);
	table->nbr_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->start_time = get_time() + table->nbr_philos * 10;
	if (ac == 6)
		table->nbr_must_eat = ft_atoi(av[5]);
	else
		table->nbr_must_eat = 0;
	if (table->nbr_philos < 1 || table->time_to_die < 60
		|| table->time_to_eat < 60 || table->time_to_sleep < 60
		|| (ac == 6 && table->nbr_must_eat < 1))
	{
		ft_putstr_fd("Error: wrong arguments\n", 2);
		return (1);
	}
	return (0);
}
