/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_filtering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:03:34 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:47:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** is_input_redir_target
**
** This function checks if a token is the target of an input
** redirection.
** - Iterate through the token list until reaching 'curr',
**   keeping track of the previous token.
** - If the previous token exists and its type is TK_IN ('<')
**   or TK_HEREDOC ('<<'), then 'curr' is a redirection target.
** - Return 1 if curr is an input redirection target,
**   otherwise return 0.
*/
int	is_input_redir_target(t_token *tokens, t_token *curr)
{
	t_token	*prev;
	t_token	*temp;

	prev = NULL;
	temp = tokens;
	while (temp && temp != curr)
	{
		prev = temp;
		temp = temp->next;
	}
	if (prev && (prev->type == TK_IN || prev->type == TK_HEREDOC))
		return (1);
	return (0);
}

/*
** is_redirection_file
**
** This function checks if a token represents a file used in a
** redirection.
** - If curr is the first token in the list, return 0 because it
**   cannot be a redirection target.
** - Otherwise, find the token immediately before curr.
** - If the previous token type is TK_OUT ('>'), TK_APPEND ('>>'),
**   TK_IN ('<'), or TK_HEREDOC ('<<'), then curr is the file
**   associated with that redirection.
** - Return 1 if curr is a redirection file, otherwise 0.
*/
int	is_redirection_file(t_token *tokens, t_token *curr)
{
	t_token	*prev;

	if (curr == tokens)
		return (0);
	prev = tokens;
	while (prev->next && prev->next != curr)
		prev = prev->next;
	if (prev && (prev->type == TK_OUT || prev->type == TK_APPEND
			|| prev->type == TK_IN || prev->type == TK_HEREDOC))
		return (1);
	return (0);
}

/*
** count_non_redirection_words
**
** This function counts word tokens that are not used as
** redirection files.
** - Iterate through each token in the list.
** - If the token type is TK_WORD and it is not a redirection
**   target (checked with is_redirection_file()), increase count.
** - Return the total number of non-redirection word tokens.
*/
int	count_non_redirection_words(t_token *tokens)
{
	t_token	*curr;
	int		word_count;

	word_count = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_WORD && !is_redirection_file(tokens, curr))
			word_count++;
		curr = curr->next;
	}
	return (word_count);
}

/*
** copy_args_to_array
**
** This function copies word tokens into a string array for
** command execution.
** - Iterate through the token list while filling up to
**   word_count elements in args.
** - For each TK_WORD token:
**     * If it is not a redirection file (checked with
**       is_redirection_file()), duplicate its value and store
**       it in the args array.
**     * If duplication fails, free the args array and return NULL.
** - Continue until all valid arguments are copied.
** - Return the filled args array.
*/
char	**copy_args_to_array(t_token *tokens, char **args, int word_count)
{
	t_token	*curr;
	int		i;

	curr = tokens;
	i = 0;
	while (curr && i < word_count)
	{
		if (curr->type == TK_WORD)
		{
			if (!is_redirection_file(tokens, curr))
			{
				args[i] = ft_strdup(curr->value);
				if (!args[i])
				{
					free_args_array(args);
					return (NULL);
				}
				i++;
			}
		}
		curr = curr->next;
	}
	return (args);
}

/*
** create_args_without_redirection
**
** This function builds an array of command arguments excluding
** redirection files.
** - Count the number of non-redirection word tokens using
**   count_non_redirection_words().
** - If no valid words are found, return NULL.
** - Allocate an array of strings with space for word_count + 1
**   (extra slot for the NULL terminator).
** - If allocation fails, return NULL.
** - Fill the array by copying tokens with copy_args_to_array().
** - If copying fails, return NULL.
** - Set the last element to NULL and return the args array.
*/
char	**create_args_without_redirection(t_token *tokens)
{
	int		word_count;
	char	**args;

	word_count = count_non_redirection_words(tokens);
	if (word_count == 0)
		return (NULL);
	args = calloc(sizeof(char *), word_count + 1);
	if (!args)
		return (NULL);
	args = copy_args_to_array(tokens, args, word_count);
	if (!args)
		return (NULL);
	args[word_count] = NULL;
	return (args);
}
