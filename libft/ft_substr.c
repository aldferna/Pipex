/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:00:32 by aldferna          #+#    #+#             */
/*   Updated: 2024/10/07 16:52:17 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str_new;
	size_t	x;

	x = ft_strlen((char *)s);
	if (start > x)
		return (ft_strdup(""));
	if ((x - start) < len)
		len = x - start;
	str_new = (char *)malloc((len + 1) * (sizeof(char)));
	if (!str_new)
		return (NULL);
	ft_strlcpy(str_new, s + start, len + 1);
	return (str_new);
}
