/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:22:32 by aldferna          #+#    #+#             */
/*   Updated: 2024/10/09 16:49:43 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	**ft_first(const char *s, char c)
{
	int		count;
	int		i;
	char	**matrix;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
			count++;
		i++;
	}
	matrix = ft_calloc((count + 1), sizeof(char *));
	if (!matrix)
	{
		free(matrix);
		return (NULL);
	}
	return (matrix);
}

static void	ft_free(char **matrix, int index)
{
	while (index >= 0)
	{
		free(matrix[index]);
		index--;
	}
	free(matrix);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	int		i;
	int		start;
	char	**matrix;

	matrix = ft_first(s, c);
	if (!matrix)
		return (free(matrix), NULL);
	index = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (start < i)
		{
			matrix[index] = ft_substr(s, start, i - start);
			if (!matrix[index++])
				return (ft_free(matrix, index), NULL);
		}
	}
	return (matrix);
}

/*int	main(void)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split("eloreeeem iipsum dolon, mipeiei", 'i');
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	return (0);
}*/
