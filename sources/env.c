/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathanael <nervin@student.42adel.org.au    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:51:22 by Nathanael         #+#    #+#             */
/*   Updated: 2022/06/06 14:52:25 by Nathanael        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(void)
{
	printf("PATH: %s\n", getenv("PATH"));
	printf("HOME: %s\n", getenv("HOME"));
	printf("ROOT: %s\n", getenv("ROOT"));
}
