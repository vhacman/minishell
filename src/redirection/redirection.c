#include "../../include/minishell.h"

/* =============================== */
/*      GESTIONE FILE              */
/* =============================== */

// Apre file con i flag corretti in base al tipo di redirezione
static int open_file_with_type(char *filename, int redirect_type)
{
    int fd;
    int flags;
    
    if (redirect_type == TK_OUT)
    {
        // > : Sovrascrivi il file
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    }
    else if (redirect_type == TK_APPEND)
    {
        // >> : Aggiungi al file esistente
        flags = O_WRONLY | O_CREAT | O_APPEND;
    }
    else
    {
        return -1; // Tipo non supportato
    }
    
    fd = open(filename, flags, 0644);
    
    if (fd == -1)
        perror("minishell");
    
    return fd;
}

/* =============================== */
/*      CREAZIONE ARGS SENZA REDIREZIONE */
/* =============================== */

// Conta i token TK_WORD escludendo quelli dopo redirezioni
static int count_args_without_redirection(t_token *tokens)
{
    t_token *curr;
    t_token *prev;
    int word_count = 0;
    
    curr = tokens;
    prev = NULL;
    while (curr)
    {
        if (curr->type == TK_WORD)
        {
            // Se il token precedente era una redirezione, salta questo filename
            if (!(prev && (prev->type == TK_OUT || prev->type == TK_APPEND || 
                          prev->type == TK_IN || prev->type == TK_HEREDOC)))
            {
                word_count++;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    
    return word_count;
}

// Crea array di argomenti escludendo i token di redirezione
char **create_args_without_redirection(t_token *tokens)
{
    t_token *curr;
    t_token *prev;
    int word_count;
    char **args;
    int i = 0;
    
    // 1. CONTA I TOKEN TK_WORD (escludendo redirezioni)
    word_count = count_args_without_redirection(tokens);
    
    // 2. ALLOCA ARRAY
    args = calloc(sizeof(char *), word_count + 1);
    if (!args)
        return NULL;
    
    // 3. COPIA GLI ARGOMENTI (escludendo filename)
    curr = tokens;
    prev = NULL;
    while (curr && i < word_count)
    {
        if (curr->type == TK_WORD)
        {
            // Se il token precedente era una redirezione, salta questo filename
            if (!(prev && (prev->type == TK_OUT || prev->type == TK_APPEND ||
                          prev->type == TK_IN || prev->type == TK_HEREDOC)))
            {
                args[i] = ft_strdup(curr->value);
                if (!args[i])
                {
                    // Libera memoria in caso di errore
                    while (--i >= 0)
                        free(args[i]);
                    free(args);
                    return NULL;
                }
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
/*      FUNZIONE PRINCIPALE        */
/* =============================== */

// Funzione principale che gestisce redirezioni con token
int handle_redirection_with_tokens(t_token *tokens, t_shell *shell)
{
    t_token *curr;
    char *filename;
    int file_fd;
    int saved_fd;
    int new_fd;

    curr = tokens;
    file_fd = -1;
    
    // Scansiona tutti i token per trovare redirezioni
    while (curr != NULL)
    {
        if (curr->type == TK_OUT || curr->type == TK_APPEND)
        {
            // Verifica che ci sia un token successivo valido
            if (curr->next == NULL || curr->next->type != TK_WORD)
            {
                ft_putstr_fd("minishell: syntax error near redirection\n", 2);
                if (file_fd != -1)
                    close(file_fd);
                return -1;
            }

            filename = curr->next->value;

            // Apri il nuovo file
            new_fd = open_file_with_type(filename, curr->type);
            if (new_fd == -1)
            {
                if (file_fd != -1)
                    close(file_fd);
                return -1;
            }

            // Se avevamo già un file aperto, chiudilo (l'ultimo vince)
            if (file_fd != -1)
                close(file_fd);

            file_fd = new_fd;
            shell->redirect_type = curr->type;
        }
        curr = curr->next;
    }

    // Se abbiamo trovato almeno una redirezione, setup del redirect
    if (file_fd != -1)
    {
        // Salva stdout originale
        saved_fd = dup(STDOUT_FILENO);
        if (saved_fd == -1)
        {
            perror("minishell");
            close(file_fd);
            return -1;
        }

        // Redirigi stdout verso il file
        if (dup2(file_fd, STDOUT_FILENO) == -1)
        {
            perror("minishell");
            close(file_fd);
            close(saved_fd);
            return -1;
        }

        close(file_fd);
        shell->saved_stdout = saved_fd;
    }
    
    restore_redirection(shell);
    return 0;
}

// Ripristina i file descriptor originali
void restore_redirection(t_shell *shell)
{
    if ((shell->redirect_type == TK_OUT || shell->redirect_type == TK_APPEND) 
        && shell->saved_stdout != -1)
    {
        dup2(shell->saved_stdout, STDOUT_FILENO);
        close(shell->saved_stdout);
        shell->saved_stdout = -1;
        shell->redirect_type = 0;
    }
}
