/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isspace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:27:30 by aldferna          #+#    #+#             */
/*   Updated: 2025/02/05 19:10:40 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isspace_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}
