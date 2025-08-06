#include "../../include/minishell.h"
/* =============================== */
/*      RICERCA TOKEN REDIREZIONE  */
/* =============================== */
// Trova il primo token di redirezione nella lista
t_token *find_redirection_token(t_token *tokens, int *redirect_type)
{
    t_token *curr = tokens;
    
    while (curr)
    {
        if (curr->type == TK_OUT || curr->type == TK_APPEND)
        {
            *redirect_type = curr->type;
            return curr;  // Ritorna il token dell'operatore
        }
        curr = curr->next;
    }
    
    *redirect_type = 0;
    return NULL;  // Nessuna redirezione trovata
}
// Ottiene il filename dal token successivo all'operatore
char *get_filename_from_next_token(t_token *redirect_token)
{
    t_token *next_token;
    
    if (!redirect_token || !redirect_token->next)
        return NULL;
    
    next_token = redirect_token->next;
    
    // Il filename deve essere un TK_WORD
    if (next_token->type != TK_WORD)
        return NULL;
    
    return ft_strdup(next_token->value);
}
/* =============================== */
/*      GESTIONE FILE              */
/* =============================== */
// Apre file con i flag corretti in base al tipo di redirezione
int open_file_with_type(char *filename, int redirect_type)
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
// Crea array di argomenti escludendo i token di redirezione
char **create_args_without_redirection(t_token *tokens)
{
    t_token *curr;
    t_token *prev;
    int word_count = 0;
    char **args;
    int i = 0;
    
    // 1. CONTA I TOKEN TK_WORD (escludendo redirezioni)
    curr = tokens;
    prev = NULL;
    while (curr)
    {
        if (curr->type == TK_WORD)
        {
            // Se il token precedente era una redirezione, salta questo filename
            if (!(prev && (prev->type == TK_OUT || prev->type == TK_APPEND)))
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
    
    // 3. COPIA GLI ARGOMENTI (escludendo filename)
    curr = tokens;
    prev = NULL;
    while (curr && i < word_count)
    {
        if (curr->type == TK_WORD)
        {
            // Se il token precedente era una redirezione, salta questo filename
            if (!(prev && (prev->type == TK_OUT || prev->type == TK_APPEND)))
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
/*      FUNZIONE PRINCIPALE        */
/* =============================== */
// Funzione principale che gestisce redirezioni con token
int handle_redirection_with_tokens(t_token *tokens, t_shell *shell)
{
    t_token *curr = tokens;
    t_token *next_token;
    char *filename = NULL;
    int file_fd = -1;
    int saved_fd = -1;

    while (curr)
    {
        if (curr->type == TK_OUT || curr->type == TK_APPEND)
        {
            if (!curr->next || curr->next->type != TK_WORD)
            {
                ft_putstr_fd("minishell: syntax error near redirection\n", 2);
                if (file_fd != -1) close(file_fd);
                return -1;
            }

            filename = curr->next->value;

            // Apri file con flags corretti
            int flags = (curr->type == TK_OUT) ?
                (O_WRONLY | O_CREAT | O_TRUNC) :
                (O_WRONLY | O_CREAT | O_APPEND);

            int new_fd = open(filename, flags, 0644);
            if (new_fd == -1)
            {
                perror("minishell");
                if (file_fd != -1) close(file_fd);
                return -1;
            }

            // Chiudi fd precedente (solo se non è il primo)
            if (file_fd != -1)
                close(file_fd);

            file_fd = new_fd;
            shell->redirect_type = curr->type; // Salva ultimo tipo
        }
        curr = curr->next;
    }

    if (file_fd != -1)
    {
        saved_fd = dup(1); // salva stdout originale
        if (saved_fd == -1)
        {
            perror("minishell");
            close(file_fd);
            return -1;
        }

        if (dup2(file_fd, 1) == -1)
        {
            perror("minishell");
            close(file_fd);
            close(saved_fd);
            return -1;
        }

        close(file_fd);
        shell->saved_stdout = saved_fd;
    }

    return 0;
}


    // Ripristina i file descriptor originali
void restore_redirection(t_shell *shell)
{
    if ((shell->redirect_type == TK_OUT || shell->redirect_type == TK_APPEND) &&
        shell->saved_stdout != -1)
    {
        dup2(shell->saved_stdout, 1);
        close(shell->saved_stdout);
        shell->saved_stdout = -1;
    }
}
