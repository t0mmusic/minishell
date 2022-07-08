/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 09:21:16 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/08 15:30:54 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	Creates a substring of the characters between quotes, quotes inclusive
 * @param	str: The users input from the prompt
 * @param	current: current index of str
 * @returns	ret: substring between quotes
**/

static char	*sub_quotes(char *str, int *current)
{
	char	end;
	char	*ret;
	int		i;

	i = *current;
	end = str[i];
	i++;
	while (str[i] && str[i] != end)
		i++;
	ret = ft_substr(str, *current, i - *current + 1);
	*current = i + 1;
	return (ret);
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
	t_list	*lst;
	int		i;

	lst = NULL;
	i = *current;
	while (str[i] && !ft_isspace(str[i]))
	{
		if ((str[i] == '|' || str[i] == '&' || str[i] == ';')
			|| (is_bookend(str, &i) && (str[i] == '\'' || str[i] == '\"')))
		{
			ft_lstadd_back(&lst,
				ft_lstnew(ft_substr(str, *current, i - *current)));
			*current = i;
			if (str[i] == '|' || str[i] == '&' || str[i] == ';')
				return (sanitise_tokens(lst));
			ft_lstadd_back(&lst, ft_lstnew(sub_quotes(str, &i)));
			*current = i;
		}
		else
			i++;
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, *current, i - *current)));
	*current = i;
	return (sanitise_tokens(lst));
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
		if (str[i] == '|' || str[i] == '&' || str[i] == ';')
			extra_token(&inputs, str, &i);
		if (and_or(ft_lstlast(inputs)->content) == true)
		{
			ft_lstadd_back(&inputs,
				ft_lstnew(ft_substr(str, i, ft_strlen(str) - i)));
			return (inputs);
		}
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

	inputs = ft_lstnew("Head");
	head = arg_list(inputs, str);
	args = malloc(sizeof(*args) * ft_lstsize(inputs));
	i = 0;
	while (inputs->next)
	{
		if (ft_strcmp("\\", inputs->next->content))
			args[i] = inputs->next->content;
		else
			i--;
		inputs = inputs->next;
		i++;
	}
	add_env(ft_strjoin("_=", args[i - 1]), false);
	args[i] = NULL;
	freelist(head);
	g_program.user_inputs = args;
}
