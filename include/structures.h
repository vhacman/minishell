/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:12:25 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/21 13:19:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/* =============================== */
/*         CORE STRUCTURES         */
/* =============================== */

/*
** t_cmd: Represents a single parsed command.
** args: NULL-terminated array of argument strings.
** path: full executable path resolved by the shell, or NULL for builtins
** fd_in/out: file descriptors for input/output redirection (default 0/1)
** next: pointer to next command in a pipeline (linked list)
*/
typedef struct s_cmd
{
	char			**args;
	char			*path;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	int				type;
}	t_cmd;

/*
** t_token:
** Linked list node representing a token produced by lexical analysis.
** value: string content of the token (e.g., command, argument, operator)
** type: token type as defined above (TK_WORD, TK_PIPE, etc.)
*/
typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

/*
** t_env:
** Linked list node representing an environment variable.
** key/value: strings for variable name and value
** exported: boolean flag indicating if variable is exported to child processes
*/
typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

/*
** t_shell: Main shell context structure holding all runtime state.
**
** line: current input line read from user
** tokens: linked list of tokens from lexical analysis
** cmds: linked list of parsed commands
** env: linked list of environment variables
** exit_status: last command exit code (for $? expansion)
** args: temporary array of args for current command execution
*/
typedef struct s_shell
{
	char		*line;
	t_token		*tokens;
	t_cmd		*cmds;
	t_env		*env;
	int			exit_status;
	char		**args;
	char		*program_name;
}	t_shell;

/* =============================== */
/*       UTILITY STRUCTURES        */
/* =============================== */
/*
** t_token_context:
** Context structure for token parsing operations.
** Contains all necessary information for token processing functions.
*/
typedef struct s_token_context
{
	const char	*input;
	int			*i;
	t_token		**tokens;
	t_shell		*shell;
	int			had_whitespace;
}	t_token_context;

/*
** t_init_params:
** Parameter structure for initialization tokens functions.
*/
typedef struct s_init_params
{
	const char	*str;
	int			*i;
	t_token		**tokens;
	t_shell		*shell;
}	t_init_params;

/*
**	Struttura per rappresentare una redirezione.
**	Contiene il tipo di redirezione e il nome del file target.
*/
typedef struct s_redirection
{
	int						type;		// Tipo: TK_OUT, TK_APPEND, TK_IN, TK_HEREDOC
	char					*filename;	// Nome del file per la redirezione
	struct s_redirection	*next;		// Puntatore alla prossima redirezione
}	t_redirection;

/*
**	Struttura per rappresentare un comando.
**	Contiene gli argomenti, le redirezioni e i file descriptor.
*/
typedef struct s_command
{
	char				**args;			// Array di argomenti (argv)
	t_redirection		*redirections;	// Lista delle redirezioni
	int					input_fd;		// File descriptor per input (se redirection)
	int					output_fd;		// File descriptor per output (se redirection)
	struct s_command	*next;			// Puntatore al prossimo comando (per pipeline)
}	t_command;

/*
**	Enum per i tipi di token (già presente nel tuo codice, ma lo riporto per chiarezza)
*/
typedef enum e_token_type
{
	TK_WORD,		// Parola normale
	TK_PIPE,		// Pipe |
	TK_OUT,			// Redirezione output >
	TK_APPEND,		// Redirezione output append >>
	TK_IN,			// Redirezione input <
	TK_HEREDOC,		// Heredoc <<
	TK_EOF,			// Fine input
}	t_token_type;


#endif
