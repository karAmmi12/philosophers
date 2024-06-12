/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:16:33 by kammi             #+#    #+#             */
/*   Updated: 2024/06/12 17:22:12 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->m_last_meal);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->table->m_last_meal);
	if (philo->table->nbr_philos == 1)
	{
		ft_usleep(philo->table->time_to_die, philo->table);
		if (!death(philo->table))
			print_msg(philo, DEAD);
		return (NULL);
	}
	if (philo->position % 2)
		ft_usleep(philo->table->time_to_eat, philo->table);
	while (!death(philo->table))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->nbr_philos)
	{
		table->philos[i].last_meal = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL,
				&philo_routine, &table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&table->death_thread, NULL, &death_monitor, table))
		return (1);
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(table->death_thread, NULL))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (parser(argc, argv, &table))
		return (1);
	if (init_table(&table))
		return (1);
	if (init_mutex(&table))
		return (1);
	if (start_simulation(&table))
		return (1);
	cleaning(&table);
	return (0);
}
