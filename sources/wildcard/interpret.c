/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:02:26 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/11 11:02:57 by jbrown           ###   ########.fr       */
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
	add_interp_token(lst, i, str, ";");
	add_interp_token(lst, i, str, "&&");
	add_interp_token(lst, i, str, "||");
	add_interp_token(lst, i, str, "|");
	add_interp_token(lst, i, str, ")");
	add_interp_token(lst, i, str, "(");
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
	if (!ft_strcmp(token, ";") || !ft_strcmp(token, "(")
		|| !ft_strcmp(token, ")"))
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
 * ! Need to keep track of initial user_inputs pointer to free at the end
 * ! Probably need to update the whole iteration thing
**/

void	next_command(void)
{
	g_program.user_inputs = update_array(g_program.user_inputs);
	if (!g_program.user_inputs)
		return ;
	if (!and_or(g_program.user_inputs[0]) || !g_program.user_inputs[1])
	{
		free_array(g_program.user_inputs);
		g_program.user_inputs = NULL;
		return ;
	}
	if (!ft_strcmp(g_program.user_inputs[0], "("))
	{
		parentheses();
		return ;
	}
	g_program.user_inputs = realloc_back(g_program.user_inputs,
			g_program.user_inputs[1]);
	split_agrs(*g_program.user_inputs);
	command();
}

/**
 * @brief	executes a command entered by the user
**/

void	command(void)
{
	if (g_program.user_inputs && !inbuilt_check()
		&& !interp_token(*g_program.user_inputs))
	{
		g_program.pid = fork();
		if (!g_program.pid)
		{
			check_pipes();
		}
		waitpid(0, &g_program.exit_status, 0);
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
		|| !ft_strcmp(token, "&&")
		|| !ft_strcmp(token, ")")
		|| !ft_strcmp(token, "("))
	{
		return (true);
	}
	return (false);
}
