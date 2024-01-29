/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:56:21 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/29 12:18:47 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	merge_to_array(int *sub_index, int *index, char **sub_arr,
	char **arr)
{
	arr[*index] = sub_arr[*sub_index];
	(*index)++;
	(*sub_index)++;
}

static void	merge(char **left, char **right, char **arr[], int len)
{
	int	left_len;
	int	right_len;
	int	i;
	int	l;
	int	r;

	left_len = len / 2;
	right_len = len - left_len;
	i = 0;
	l = 0;
	r = 0;
	while (l < left_len && r < right_len)
	{
		if (ft_strcmp(left[l], right[r]) < 0)
			merge_to_array(&l, &i, left, *arr);
		else
			merge_to_array(&r, &i, right, *arr);
	}
	while (l < left_len)
		merge_to_array(&l, &i, left, *arr);
	while (r < right_len)
		merge_to_array(&r, &i, right, *arr);
}

void	ft_merge_sort(int len, char **arr)
{
	int		middle;
	char	**left;
	char	**right;
	int		j;
	int		i;

	if (len <= 1)
		return ;
	middle = len / 2;
	left = ft_calloc(middle, sizeof(char *));
	right = ft_calloc(len - middle, sizeof(char *));
	j = -1;
	i = -1;
	while (++i < len)
	{
		if (i < middle)
			left[i] = arr[i];
		else
			right[++j] = arr[i];
	}
	ft_merge_sort(middle, left);
	ft_merge_sort(len - middle, right);
	merge(left, right, &arr, len);
	free(left);
	free(right);
}
