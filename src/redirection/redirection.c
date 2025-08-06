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
        t_token *redirect_token;
        int redirect_type;
        char *filename;
        int file_fd;
        int saved_fd;
        int target_fd;
        
        // 1. TROVA IL TOKEN DI REDIREZIONE
        redirect_token = find_redirection_token(tokens, &redirect_type);
        
        if (!redirect_token)
            return 0; // Nessuna redirezione
        
        // 2. ESTRAE IL FILENAME DAL TOKEN SUCCESSIVO
        filename = get_filename_from_next_token(redirect_token);
        if (!filename)
        {
            ft_putstr_fd("minishell: syntax error near redirection\n", 2);
            return -1;
        }
        
        // 3. APRE IL FILE CON FLAGS APPROPRIATI
        file_fd = open_file_with_type(filename, redirect_type);
        if (file_fd == -1)
        {
            free(filename);
            return -1;
        }
        
        // 4. DETERMINA QUALE FD SALVARE E REDIRIGERE
        target_fd = 1; // stdout per > e >>
        saved_fd = dup(1);
        
        if (saved_fd == -1)
        {
            close(file_fd);
            free(filename);
            return -1;
        }
        
        // 5. REDIRIGI IL FILE DESCRIPTOR
        if (dup2(file_fd, target_fd) == -1)
        {
            close(file_fd);
            close(saved_fd);
            free(filename);
            return -1;
        }
        
        close(file_fd); // Chiudi fd originale del file
        
        // 6. SALVA I FD PER IL RIPRISTINO SUCCESSIVO
        // Nota: saved_stdout dovrebbe essere aggiunto alla struct t_shell
        // shell->saved_stdout = saved_fd;
        
        free(filename);
        return saved_fd; // Ritorna il saved_fd per il ripristino successivo
    }

    // Ripristina i file descriptor originali
    void restore_redirection(int saved_stdout, int redirect_type)
    {
        if ((redirect_type == TK_OUT || redirect_type == TK_APPEND) && 
            saved_stdout != -1)
        {
            dup2(saved_stdout, 1);
            close(saved_stdout);
        }
    }