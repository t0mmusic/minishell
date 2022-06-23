/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 09:21:16 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/23 14:40:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/*	Need to add a function that expands environment variables. I am still not
	sure how to do this...	*/

/*	Checks a string from a ' or a " to see if it has a match. Returns true
	if it does, false if it doesn't.	*/

static bool	is_bookend(char *str, int *current)
{
	char	bookend;
	int		i;

	i = *current;
	if (str[i] != '\'' && str[i] != '\"')
		return (true);
	if (!str[i + 1])
		return (false);
	bookend = str[i];
	i += 1;
	while (str[i])
	{
		if (str[i] == bookend)
			return (true);
		i++;
	}
	*current += 1;
	return (false);
}

/*	Finds strings of characters, either based on contiguous characters with no
	spaces, or strings bookended by quotes.	*/

static char	*ft_cpystr(char *str, int *current)
{
	char	end;
	char	*ret;
	int		i;

	i = *current;
	if (str[i] == '\'' || str[i] == '\"')
	{
		end = str[i];
		i++;
		while (str[i] && str[i] != end)
			i++;
		ret = ft_substr(str, *current + 1, i - *current - 1);
		*current = i + 1;
	}
	else
	{
		while (str[i] && !ft_isspace(str[i]))
		{
			i++;
		}
		ret = ft_substr(str, *current, i - *current);
		*current = i;
	}
	return (ret);
}

/*	Creates a linked list of all the inputs entered by the user.	*/

static t_list	*arg_list(t_list *inputs, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && !ft_isspace(str[i]) && is_bookend(str, &i))
			ft_lstadd_back(&inputs, ft_lstnew(ft_cpystr(str, &i)));
	}
	return (inputs);
}

/*	Splits all of the user inputs into separate strings based mostly on spaces,
	but also based on whether they are in quotes.	*/

void	split_agrs(char *str)
{
	int		i;
	char	**args;
	t_list	*inputs;
	t_list	*head;

	free_inputs(g_program.user_inputs);
	inputs = ft_lstnew("Head");
	head = arg_list(inputs, str);
	args = malloc(sizeof(*args) * ft_lstsize(inputs));
	i = 0;
	while (inputs->next)
	{
		args[i] = inputs->next->content;
		inputs = inputs->next;
		i++;
	}
	args[i] = NULL;
	freelist(head);
	g_program.user_inputs = args;
}
