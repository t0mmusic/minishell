/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:02:26 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/08 15:23:54 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_prog	g_program;

/**
 * @brief	If one of the operators is found, it will add it as a seperate token
 * * ;  :	Perform one operation, then the next
 * * && :	If the first operation is successful, execute the next
 * * || :	If the first operation is NOT successful, execute the next
 * @param	lst: reference to the token list being added to
 * @param	str: string being split into tokens
 * @param	i: current index of str
**/

void	extra_token(t_list **lst, char *str, int *i)
{
	if (!strncmp(&str[*i], "|", 1))
	{
		ft_lstadd_back(lst, ft_lstnew(ft_strdup("|")));
		*i += 1;
	}
	if (!strncmp(&str[*i], ";", 1))
	{
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(";")));
		*i += 1;
	}
	if (!strncmp(&str[*i], "&&", 2))
	{
		ft_lstadd_back(lst, ft_lstnew(ft_strdup("&&")));
		*i += 2;
	}
	if (!strncmp(&str[*i], "||", 2))
	{
		ft_lstadd_back(lst, ft_lstnew(ft_strdup("||")));
		*i += 2;
	}
}

/**
 * @brief	Checks to see if the current token is ;, && or ||. ; will return
 * true in all cases, && will return true if the last command executed
 * successfully, and || will return true if the last command did NOT execute
 * successfully.
 * @param	token: the token being compared
 * @returns	boolean true if match is found, false if not
**/

bool	and_or(char *token)
{
	if (!ft_strcmp(token, ";"))
		return (true);
	if (!ft_strcmp(token, "&&") && !g_program.exit_status)
		return (true);
	if (!ft_strcmp(token, "||") && g_program.exit_status)
		return (true);
	return (false);
}

/**
 * @brief	If the user has entered multiple commands seperated by ;, && or ||,
 * this function will iterate to the next function in the list and determine if
 * that command will be executed.
**/

void	next_command(void)
{
	while (*g_program.user_inputs && !interp_token(*g_program.user_inputs))
	{
		iterate_user_inputs();
	}
	if (!*g_program.user_inputs)
		g_program.user_inputs = NULL;
	else
	{
		if (and_or(*g_program.user_inputs) == false)
		{
			g_program.user_inputs = NULL;
			return ;
		}
		iterate_user_inputs();
		if (*g_program.user_inputs)
		{
			split_agrs(*g_program.user_inputs);
			command();
		}
	}
}

/**
 * @brief	executes a command entered by the user
**/

void	command(void)
{
	if (!inbuilt_check())
	{
		g_program.pid = fork();
		if (!g_program.pid)
		{
			check_pipes();
		}
		waitpid(g_program.pid, &g_program.exit_status, 0);
	}
	while (g_program.user_inputs)
		next_command();
}

/**
 * @brief	Checks to see if the current token is ;, && or ||.
 * @param	token: the token being compared
 * @returns	boolean true if match is found, false if not
**/

bool	interp_token(char *token)
{
	if (!ft_strcmp(token, ";")
		|| !ft_strcmp(token, "||")
		|| !ft_strcmp(token, "&&"))
	{
		return (true);
	}
	return (false);
}
