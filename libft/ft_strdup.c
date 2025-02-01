/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:44:34 by aldferna          #+#    #+#             */
/*   Updated: 2024/10/08 18:05:07 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str_dup;
	int		n;

	n = ft_strlen((char *)s) + 1;
	str_dup = (char *)malloc(n * sizeof(char));
	if (!str_dup)
		return (NULL);
	ft_strlcpy(str_dup, s, n);
	return (str_dup);
}
