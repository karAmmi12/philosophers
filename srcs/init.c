/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:58:03 by kammi             #+#    #+#             */
/*   Updated: 2024/06/20 12:43:01 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->m_dead, NULL))
		return (1);
	if (pthread_mutex_init(&table->m_count_meal, NULL))
		return (1);
	if (pthread_mutex_init(&table->m_print, NULL))
		return (1);
	if (pthread_mutex_init(&table->m_last_meal, NULL))
		return (1);
	//if (pthread_mutex_init(&table->m_ready, NULL))
		//return (1);
	return (0);
}

void	philo_forks_init(t_philo *philo, size_t i)
{
	if (philo->position % 2)
	{
		philo->fork_left = &philo->table->forks[i];
		philo->fork_right = &philo->table->forks[(i + 1)
			% philo->table->nbr_philos];
	}
	else
	{
		philo->fork_right = &philo->table->forks[i];
		philo->fork_left = &philo->table->forks[(i + 1)
			% philo->table->nbr_philos];
	}
}

int	init_philos(t_table *table)
{
	size_t	i;

	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philos)
		return (1);
	i = 0;
	memset(table->philos, 0, sizeof(t_philo) * table->nbr_philos);
	while (i < table->nbr_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].position = i + 1;
		table->philos[i].table = table;
		table->philos[i].count_meal = 0;
		i++;
	}
	return (0);
}

int	init_forks(t_table *table)
{
	size_t	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (!table->forks)
	{
		free(table->philos);
		return (1);
	}
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			free(table->philos);
			free(table->forks);
			return (1);
		}
		philo_forks_init(&table->philos[i], i);
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	if (init_philos(table) || init_forks(table))
		return (1);
	table->dead = 0;
	//table->ready_count = 0;
	return (0);
}
// int	init_table(t_table *table)
// {
// 	size_t	i;

// 	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
// 	if (!table->philos)
// 		return (1);
// 	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
// 	if (!table->forks)
// 	{
// 		free(table->philos);
// 		return (1);
// 	}
// 	i = 0;
// 	memset(table->philos, 0, sizeof(t_philo) * table->nbr_philos);
// 	while (i < table->nbr_philos)
// 	{
// 		if (pthread_mutex_init(&table->forks[i], NULL))
// 		{
// 			free(table->philos);
// 			free(table->forks);
// 			return (1);
// 		}
// 		table->philos[i].id = i + 1;
// 		table->philos[i].position = i + 1;
// 		table->philos[i].table = table;
// 		table->philos[i].count_meal = 0;
// 		forks_init(&table->philos[i], i);
// 		i++;
// 	}
// 	table->dead = 0;
// 	return (0);
// }
