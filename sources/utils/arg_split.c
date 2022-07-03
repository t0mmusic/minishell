/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 09:21:16 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/03 15:37:39 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Checks a string from a ' or a " to see if it has a match.
 * @param	str: The users input from the prompt
 * @param	current: current index of str
 * @returns	boolean true if match is found, false if not
**/

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

/**
 * @brief	Finds strings of characters, either based on contiguous characters
 * with no spaces, or strings bookended by quotes.
 * @param	str: The users input from the prompt
 * @param	current: current index of str
 * @returns	ret: token of user input
**/

static char	*ft_cpystr(char *str, int *current)
{
	char	end;
	char	*ret;
	int		i;

	i = *current;
	end = str[i];
	if (str[i] == '\'' || str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != end)
			i++;
		ret = ft_substr(str, *current + 1, i - *current - 1);
		*current = i + 1;
	}
	else
	{
		while (str[i] && !ft_isspace(str[i]))
			i++;
		ret = ft_substr(str, *current, i - *current);
		*current = i;
	}
	if (end != '\'')
		return (expand_string(ret));
	return (ret);
}

/**
 * @brief	Creates a linked list of all the inputs entered by the user.
 * * A linked list was chosen because it is difficult to determine how many
 * * tokens are needed right away. Being able to dynamically expand the list
 * * is crucial
 * @param	inputs: list of user inputs
 * @param	str: The users input from the prompt
 * @returns	inputs: list of user inputs
**/

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

/**
 * @brief	Splits all of the user inputs into separate strings based mostly on
 * spaces, but also based on whether they are in quotes.
 * @param	str: The users input from the prompt
**/

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
