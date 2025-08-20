#include "../../include/minishell.h"


t_token *find_input_redirection_token(t_token *tokens, int *redirect_type)
{
	t_token *curr = tokens;
	
	while (curr)
	{
		if (curr->type == TK_IN || curr->type == TK_HEREDOC)
		{
			*redirect_type = curr->type;
			return curr;
		}
		curr = curr->next;
	}
	
	*redirect_type = 0;
	return NULL;
}

static int process_heredoc_line(int write_fd, char *line, t_shell *shell)
{
	char *expanded_line;
	
	expanded_line = expand_variables(line, shell);
	if (!expanded_line)
		return -1;
	
	if (write(write_fd, expanded_line, ft_strlen(expanded_line)) == -1 ||
		write(write_fd, "\n", 1) == -1)
	{
		perror("minishell: write");
		free(expanded_line);
		return -1;
	}
	free(expanded_line);
	return 0;
}

static int read_heredoc_lines(int write_fd, char *delimiter, t_shell *shell)
{
	char *line;
	
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", 2);
			break;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (process_heredoc_line(write_fd, line, shell) == -1)
		{
			free(line);
			return -1;
		}
		free(line);
	}
	return 0;
}

int create_heredoc_pipe(char *delimiter, t_shell *shell)
{
	int pipe_fd[2];
	int result;
	
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return -1;
	}
	result = read_heredoc_lines(pipe_fd[1], delimiter, shell);
	close(pipe_fd[1]);
	if (result == -1)
	{
		close(pipe_fd[0]);
		return -1;
	}
	return pipe_fd[0];
}

// Funzione helper per verificare se un token è un filename di redirezione
static int is_redirection_filename(t_token *tokens, t_token *curr)
{
	t_token *prev = NULL;
	t_token *temp = tokens;
	
	while (temp && temp != curr)
	{
		prev = temp;
		temp = temp->next;
	}
	if (prev && (prev->type == TK_IN || prev->type == TK_HEREDOC))
		return (1);
	return (0);
}

// Funzione per contare i token validi (escludendo filename di redirezioni)
static int count_valid_args(t_token *tokens)
{
	t_token *curr;
	int word_count = 0;
	
	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_WORD)
		{
			if (!is_redirection_filename(tokens, curr))
				word_count++;
		}
		curr = curr->next;
	}
	return (word_count);
}

// Funzione principale per creare l'array di argomenti
char **create_args_without_input_redirection(t_token *tokens)
{
	t_token *curr;
	int word_count;
	char **args;
	int i = 0;
	
	word_count = count_valid_args(tokens);
	args = calloc(sizeof(char *), word_count + 1);
	if (!args)
		return (NULL);
	curr = tokens;
	while (curr && i < word_count)
	{
		if (curr->type == TK_WORD)
		{
			if (!is_redirection_filename(tokens, curr))
			{
				args[i] = ft_strdup(curr->value);
				i++;
			}
		}
		curr = curr->next;
	}
	args[i] = NULL;
	return (args);
}

// Funzione per applicare la redirezione input
static int apply_input_redirection(int input_fd, t_shell *shell)
{
	int saved_stdin;

	saved_stdin = dup(0);
	if (saved_stdin == -1)
	{
		perror("minishell: dup");
		close(input_fd);
		return (-1);
	}
	if (dup2(input_fd, 0) == -1)
	{
		perror("minishell: dup2");
		close(input_fd);
		close(saved_stdin);
		return (-1);
	}
	close(input_fd);
	shell->saved_stdin = saved_stdin;
	return (0);
}

static int validate_redirect_syntax(t_token *curr)
{
	if (curr->next == NULL || curr->next->type != TK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		return (-1);
	}
	return (0);
}

// 2. Funzione per aprire il file di input appropriato
static int open_input_file(t_token *curr, t_shell *shell)
{
	char *filename;
	int new_input_fd;

	filename = curr->next->value;
	if (curr->type == TK_IN)
	{
		new_input_fd = open(filename, O_RDONLY);
		if (new_input_fd == -1)
		{
			perror("minishell");
			return (-1);
		}
	}
	else if (curr->type == TK_HEREDOC)
	{
		new_input_fd = create_heredoc_pipe(filename, shell);
		if (new_input_fd == -1)
			return (-1);
	}
	else
		return (-1);
	return (new_input_fd);
}

// 3. Funzione per aggiornare il file descriptor di input
static void update_input_fd(int *input_fd, int new_input_fd)
{
	if (*input_fd != -1)
		close(*input_fd);
	*input_fd = new_input_fd;
}

// Funzione principale refactorizzata
static int handle_single_input_redirect(t_token *curr, t_shell *shell, int *input_fd)
{
	int new_input_fd;

	if (validate_redirect_syntax(curr) == -1)
	{
		if (*input_fd != -1)
			close(*input_fd);
		return (-1);
	}
	new_input_fd = open_input_file(curr, shell);
	if (new_input_fd == -1)
	{
		if (*input_fd != -1)
			close(*input_fd);
		return (-1);
	}
	update_input_fd(input_fd, new_input_fd);
	return (0);
}

// Funzione principale semplificata
int handle_input_redirection_with_tokens(t_token *tokens, t_shell *shell)
{
	t_token *curr;
	int input_fd;
	
	curr = tokens;
	input_fd = -1;
	while (curr != NULL)
	{
		if (curr->type == TK_IN || curr->type == TK_HEREDOC)
		{
			if (handle_single_input_redirect(curr, shell, &input_fd) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	if (input_fd != -1)
		return (apply_input_redirection(input_fd, shell));
	return (0);
}

void restore_input_redirection(t_shell *shell)
{
	if (shell->saved_stdin >= 0)
	{
		dup2(shell->saved_stdin, 0);
		close(shell->saved_stdin);
		shell->saved_stdin = -1;
	}
}
