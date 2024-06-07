/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:16:33 by kammi             #+#    #+#             */
/*   Updated: 2024/06/07 15:56:38 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->m_last_meal);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->table->m_last_meal);
	if (philo->position % 2)
		ft_usleep(philo->table->time_to_eat, philo->table);
	while (!philo->table->dead)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
void	set_death(t_table *table)
{
	pthread_mutex_lock(&table->m_dead);
	table->dead = 1;
	pthread_mutex_unlock(&table->m_dead);
}
int	check_death(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->m_last_meal);
	time = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->table->m_last_meal);
	// printf("time = %zu\n", time);
	// printf("time_to_die = %zu\n", philo->table->time_to_die);
	if (time >= philo->table->time_to_die)
	{
		set_death(philo->table);
		usleep(1000);
		print_msg(philo, DEAD);
		return (1);
	}
	return (0);
}

int	handle_end(t_table *table)
{
	size_t	i;
	int		ret;

	ret = 1;
	i = 0;
	while (i < table->nbr_philos)
	{
		if (check_death(&table->philos[i]))
			return (1);

		if (table->nbr_must_eat)
		{
			pthread_mutex_lock(&table->m_count_meal);
			if (table->philos[i].count_meal < table->nbr_must_eat)
				ret = 0;
			pthread_mutex_unlock(&table->m_count_meal);
		}
		i++;
	}
	if (table->nbr_must_eat && ret)
	{
		set_death(table);
		return (1);
	}
	else
		return (0);
}

void	*death_monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!table->dead)
	{
		if (handle_end(table))
			break;
		usleep(1000);
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
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine, &table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&table->death_thread, NULL, &death_monitor, table))
	{
		return (1);
	}

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

	if(parser(argc, argv, &table))
		return (1);
	if (init_table(&table))
		return (1);
	if (init_mutex(&table))
		return (free_philos(&table), 1);
	if (start_simulation(&table))
		return (1);
	printf("Simulation ended\n");
	cleaning(&table);

	return (0);
}
