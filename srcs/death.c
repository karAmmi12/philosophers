/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:19:42 by kammi             #+#    #+#             */
/*   Updated: 2024/06/20 12:59:19 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	death(t_table *table)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->m_dead);
	if (table->dead)
		ret = 1;
	pthread_mutex_unlock(&table->m_dead);
	return (ret);
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
	wait_all_philos(table->start_time);
	while (!death(table))
	{
		if (handle_end(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
