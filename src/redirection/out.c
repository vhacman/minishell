#include "../../include/minishell.h"

// Ottiene il filename dal token successivo all'operatore
char *get_filename_from_next_token(t_token *redirect_token)
{
	t_token *next_token;
	
	if (!redirect_token || !redirect_token->next)
		return NULL;
	next_token = redirect_token->next;
	if (next_token->type != TK_WORD)
		return NULL;
	return (ft_strdup(next_token->value));
}

t_token *find_redirection_token(t_token *tokens, int *redirect_type, bool input_only)
{
	t_token *curr = tokens;
	
	while (curr)
	{
		if (input_only)
		{
			if (curr->type == TK_IN || curr->type == TK_HEREDOC)
			{
				*redirect_type = curr->type;
				return curr;
			}
		}
		else
		{
			if (curr->type == TK_OUT || curr->type == TK_APPEND)
			{
				*redirect_type = curr->type;
				return curr;
			}
		}
		curr = curr->next;
	}
	*redirect_type = 0;
	return (NULL);
}

static int open_regular_file(char *filename, int token_type)
{
	int fd;
	int flags;

	if (token_type == TK_IN)
		fd = open(filename, O_RDONLY);
	else if (token_type == TK_OUT)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(filename, flags, 0644);
	}
	else if (token_type == TK_APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		fd = open(filename, flags, 0644);
	}
	else
		return (-1);
	if (fd == -1)
		perror("minishell");
	return (fd);
}

int open_file_by_type(char *filename, int token_type, t_shell *shell)
{
	if (token_type == TK_HEREDOC)
		return (create_heredoc_pipe(filename, shell));
	return (open_regular_file(filename, token_type));
}

// Funzione estratta per copiare gli argomenti
static int is_redirection_file(t_token *tokens, t_token *curr)
{
	t_token *prev;

	if (curr == tokens)
		return (0);
	
	prev = tokens;
	while (prev->next && prev->next != curr)
		prev = prev->next;
	
	if (prev && (prev->type == TK_OUT || prev->type == TK_APPEND || 
			   prev->type == TK_IN || prev->type == TK_HEREDOC))
		return (1);
	
	return (0);
}

static char **copy_args_to_array(t_token *tokens, char **args, int word_count)
{
	t_token *curr;
	int     i;

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
					while (--i >= 0)
						free(args[i]);
					free(args);
					return (NULL);
				}
				i++;
			}
		}
		curr = curr->next;
	}
	return (args);
}

int count_non_redirection_words(t_token *tokens)
{
	t_token *curr;
	int word_count;
	
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

// Seconda funzione: crea l'array di argomenti
char **create_args_without_redirection(t_token *tokens)
{
	int word_count;
	char **args;
	
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

int validate_input_redirections(t_token *tokens)
{
	t_token *curr = tokens;
	
	while (curr != NULL)
	{
		if (curr->type == TK_IN)
		{
			if (curr->next == NULL || curr->next->type != TK_WORD)
			{
				ft_putstr_fd("minishell: syntax error near redirection\n", 2);
				return (-1);
			}
			int test_fd = open(curr->next->value, O_RDONLY);
			if (test_fd == -1)
			{
				perror("minishell");
				return (-1);
			}
			close(test_fd);
		}
		else if (curr->type == TK_HEREDOC)
		{
			if (curr->next == NULL || curr->next->type != TK_WORD)
			{
				ft_putstr_fd("minishell: syntax error near redirection\n", 2);
				return (-1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

int setup_output_redirection(int file_fd, t_shell *shell)
{
	int saved_fd;

	if (file_fd == -1)
		return (0);
	
	saved_fd = dup(1);
	if (saved_fd == -1)
	{
		perror("minishell");
		close(file_fd);
		restore_input_redirection(shell);
		return (-1);
	}
	if (dup2(file_fd, 1) == -1)
	{
		perror("minishell");
		close(file_fd);
		close(saved_fd);
		restore_input_redirection(shell);
		return (-1);
	}
	close(file_fd);
	shell->saved_stdout = saved_fd;
	return (0);
}

// Prima funzione: validazione del token e apertura del file
static int open_output_file(t_token *curr, char **filename)
{
	int flags;
	int new_fd;

	if (curr->next == NULL || curr->next->type != TK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		return -1;
	}
	*filename = curr->next->value;
	if (curr->type == TK_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	new_fd = open(*filename, flags, 0644);
	if (new_fd == -1)
	{
		perror("minishell");
		return -1;
	}
	return (new_fd);
}

// Seconda funzione: gestione del file descriptor e aggiornamento dello shell
static int handle_output_redirection_token(t_token *curr, int *file_fd, t_shell *shell)
{
	char *filename;
	int new_fd;

	new_fd = open_output_file(curr, &filename);
	if (new_fd == -1)
	{
		if (*file_fd != -1)
			close(*file_fd);
		restore_input_redirection(shell);
		return -1;
	}
	
	if (*file_fd != -1)
		close(*file_fd);
	
	*file_fd = new_fd;
	shell->redirect_type = curr->type;
	return 0;
}

// Funzione principale modificata
int handle_redirection_with_tokens(t_token *tokens, t_shell *shell)
{		
	t_token *curr = tokens;
	int file_fd = -1;
	
	if (validate_input_redirections(tokens) == -1)
		return (-1);		
	if (handle_input_redirection_with_tokens(tokens, shell) == -1)
		return (-1);
	curr = tokens;
	while (curr != NULL)
	{
		if (curr->type == TK_OUT || curr->type == TK_APPEND)
		{
			if (handle_output_redirection_token(curr, &file_fd, shell) == -1)
				return -1;
		}
		curr = curr->next;
	}
	if (setup_output_redirection(file_fd, shell) == -1)
		return (-1);
	return (0);
}

void restore_redirection(t_shell *shell)
{
	if ((shell->redirect_type == TK_OUT || shell->redirect_type == TK_APPEND) && shell->saved_stdout >= 0)
	{
		dup2(shell->saved_stdout, 1);
		close(shell->saved_stdout);
		shell->saved_stdout = -1;
	}
	// Ripristina anche le redirezioni di input
	restore_input_redirection(shell);
	// Reset del tipo di redirezione
	shell->redirect_type = 0;
}