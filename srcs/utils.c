/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:33:05 by kammi             #+#    #+#             */
/*   Updated: 2024/06/12 17:30:40 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleaning(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
	pthread_mutex_destroy(&table->m_dead);
	pthread_mutex_destroy(&table->m_count_meal);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_last_meal);
}

void	print_msg(t_philo *philo, int msg)
{
	pthread_mutex_lock(&philo->table->m_print);
	if (death(philo->table) && msg != DEAD)
	{
		pthread_mutex_unlock(&philo->table->m_print);
		return ;
	}
	if (msg == DEAD)
	{
		printf("%s%09zu %zu died%s\n", RED,
			get_time() - philo->table->start_time, philo->id, RESET);
		set_death(philo->table);
	}
	else if (msg == EAT)
		printf("%s%09zu %zu is eating%s\n", BLUE,
			get_time() - philo->table->start_time, philo->id, RESET);
	else if (msg == SLEEP)
		printf("%s%09zu %zu is sleeping%s\n", YELLOW,
			get_time() - philo->table->start_time, philo->id, RESET);
	else if (msg == THINK)
		printf("%s%09zu %zu is thinking%s\n", GREEN,
			get_time() - philo->table->start_time, philo->id, RESET);
	else if (msg == FORK)
		printf("%s%09zu %zu has taken a fork%s\n", MAGENTA,
			get_time() - philo->table->start_time, philo->id, RESET);
	pthread_mutex_unlock(&philo->table->m_print);
}
