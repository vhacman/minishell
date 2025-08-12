//ANDRANNO AGGIUNTE AL PARSER


#include "../../include/minishell.h"

t_token *find_input_redirection_token(t_token *tokens, int *redirect_type)
{
    t_token *curr = tokens;
    
    while (curr)
    {
        if (curr->type == TK_IN || curr->type == TK_HEREDOC)
        {
            *redirect_type = curr->type;
            return curr;  // Ritorna il token dell'operatore
        }
        curr = curr->next;
    }
    
    *redirect_type = 0;
    return NULL;  // Nessuna redirezione trovata
}

int create_heredoc_pipe(char *delimiter, t_shell *shell)
{
    int pipe_fd[2];
    char *line;
    
    if (pipe(pipe_fd) == -1)
    {
        perror("minishell: pipe");
        return -1;
    }
    // Leggi le righe fino al delimiter
    while (1)
    {
        line = readline("> ");
        if (!line)  // EOF (Ctrl+D)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", 2);
            break;
        }
        // Se la riga è uguale al delimiter, ferma la lettura
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        // Espandi le variabili nella riga dell'heredoc
        char *expanded_line = expand_variables(line, shell);
        free(line);
        // Scrivi la riga nella pipe (con newline)
        write(pipe_fd[1], expanded_line, ft_strlen(expanded_line));
        write(pipe_fd[1], "\n", 1);
        free(expanded_line);
    }
    
    close(pipe_fd[1]);  // Chiudi il lato di scrittura
    return pipe_fd[0];  // Ritorna il lato di lettura
}

char **create_args_without_input_redirection(t_token *tokens)
{
    t_token *curr;
    t_token *prev;
    int word_count = 0;
    char **args;
    int i = 0;
    
    // 1. CONTA I TOKEN TK_WORD (escludendo redirezioni input)
    curr = tokens;
    prev = NULL;
    while (curr)
    {
        if (curr->type == TK_WORD)
        {
            // Se il token precedente era una redirezione input, salta questo filename
            if (!(prev && (prev->type == TK_IN || prev->type == TK_HEREDOC)))
            {
                word_count++;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    // 2. ALLOCA ARRAY
    args = calloc(sizeof(char *), word_count + 1);
    if (!args)
        return NULL;
    // 3. COPIA GLI ARGOMENTI (escludendo filename di input)
    curr = tokens;
    prev = NULL;
    while (curr && i < word_count)
    {
        if (curr->type == TK_WORD)
        {
            // Se il token precedente era una redirezione input, salta questo filename
            if (!(prev && (prev->type == TK_IN || prev->type == TK_HEREDOC)))
            {
                args[i] = ft_strdup(curr->value);
                i++;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    
    args[i] = NULL;
    return args;
}

/* =============================== */
/*      FUNZIONE PRINCIPALE INPUT  */
/* =============================== */
// Gestisce le redirezioni di input (< e <<)
int handle_input_redirection_with_tokens(t_token *tokens, t_shell *shell)
{
    t_token *curr;
    char *filename;
    int input_fd;
    int saved_stdin;
    
    curr = tokens;
    input_fd = -1;
    
    while (curr != NULL)
    {
        if (curr->type == TK_IN || curr->type == TK_HEREDOC)
        {
            // Controllo sintassi: deve esserci un token successivo
            if (curr->next == NULL || curr->next->type != TK_WORD)
            {
                ft_putstr_fd("minishell: syntax error near redirection\n", 2);
                if (input_fd != -1)
                    close(input_fd);
                return -1;
            }

            filename = curr->next->value;

            // Gestione diversa per < e <<
            if (curr->type == TK_IN)
            {
                // Input redirection: apri il file
                input_fd = open(filename, O_RDONLY);
            }
            else if (curr->type == TK_HEREDOC)
            {
                // Heredoc: crea pipe temporanea
                input_fd = create_heredoc_pipe(filename, shell);
            }

            if (input_fd == -1)
            {
                return -1;  // Errore già stampato dalle funzioni sopra
            }

            // Se avevamo già un input_fd precedente, chiudilo
            // (l'ultimo input redirection ha precedenza)
            if (shell->saved_stdin != -1)
            {
                close(shell->saved_stdin);
            }
        }
        curr = curr->next;
    }

    // Se abbiamo trovato una redirezione input, applica il dup2
    if (input_fd != -1)
    {
        saved_stdin = dup(0);  // Salva stdin originale
        if (saved_stdin == -1)
        {
            perror("minishell: dup");
            close(input_fd);
            return -1;
        }

        if (dup2(input_fd, 0) == -1)  // Redirigi input_fd a stdin (0)
        {
            perror("minishell: dup2");
            close(input_fd);
            close(saved_stdin);
            return -1;
        }

        close(input_fd);  // Chiudi il fd originale
        shell->saved_stdin = saved_stdin;
    }

    return 0;
}

/* =============================== */
/*      RIPRISTINO INPUT           */
/* =============================== */
// Ripristina stdin originale
void restore_input_redirection(t_shell *shell)
{
    if (shell->saved_stdin != -1)
    {
        dup2(shell->saved_stdin, 0);
        close(shell->saved_stdin);
        shell->saved_stdin = -1;
    }
}