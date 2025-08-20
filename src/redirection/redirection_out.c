//ANDRANNO AGGIUNTE AL PARSER

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
	return (ft_strdup(next_token->value));
}

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
		return -1; // Tipo non supportato
	fd = open(filename, flags, 0644);
	if (fd == -1)
		perror("minishell");
	return fd;
}

// Crea array di argomenti escludendo i token di redirezione
// Versione più sicura di create_args_without_redirection
char **create_args_without_redirection(t_token *tokens)
{
    t_token *curr;
    int word_count = 0;
    char **args;
    int i = 0;
    
    // 1. CONTA I TOKEN TK_WORD (escludendo quelli dopo redirezioni)
    curr = tokens;
    while (curr)
    {
        if (curr->type == TK_WORD)
        {
            // Controlla il token precedente in modo sicuro
            int is_redirection_file = 0;
            
            // Se non è il primo token, controlla il precedente
            if (curr != tokens)
            {
                // Trova il token precedente in modo più sicuro
                t_token *prev = tokens;
                while (prev->next && prev->next != curr)
                    prev = prev->next;
                
                if (prev && (prev->type == TK_OUT || prev->type == TK_APPEND || 
                           prev->type == TK_IN || prev->type == TK_HEREDOC))
                    is_redirection_file = 1;
            }
            
            if (!is_redirection_file)
                word_count++;
        }
        curr = curr->next;
    }
    
    // 2. ALLOCA ARRAY con controllo di sicurezza
    if (word_count == 0)
        return (NULL);
        
    args = calloc(sizeof(char *), word_count + 1);
    if (!args)
        return (NULL);
    
    // 3. COPIA GLI ARGOMENTI
    curr = tokens;
    i = 0;
    while (curr && i < word_count)
    {
        if (curr->type == TK_WORD)
        {
            // Controlla il token precedente in modo sicuro
            int is_redirection_file = 0;
            
            if (curr != tokens)
            {
                t_token *prev = tokens;
                while (prev->next && prev->next != curr)
                    prev = prev->next;
                
                if (prev && (prev->type == TK_OUT || prev->type == TK_APPEND || 
                           prev->type == TK_IN || prev->type == TK_HEREDOC))
                    is_redirection_file = 1;
            }
            
            if (!is_redirection_file)
            {
                args[i] = ft_strdup(curr->value);
                if (!args[i])  // Controllo di sicurezza
                {
                    // Libera tutto quello che abbiamo allocato
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
    args[i] = NULL;
    return (args);
}

// Funzione principale che gestisce redirezioni con token
// In redirection_out.c, sostituisci handle_redirection_with_tokens con:

int handle_redirection_with_tokens(t_token *tokens, t_shell *shell)
{		
	t_token *curr = tokens;
	char *filename;
	int file_fd = -1;
	int saved_fd;
	int flags;
	int new_fd;
		// SECONDO: Solo dopo aver verificato gli input, processa le input redirection
	if (handle_input_redirection_with_tokens(tokens, shell) == -1)
		return (-1);
	// PRIMA: Controlla se ci sono redirezioni di input e processale
	// MA non fare ancora il dup2 - solo verifica che i file esistano

	while (curr != NULL)
	{
		if (curr->type == TK_IN)
		{
			if (curr->next == NULL || curr->next->type != TK_WORD)
			{
				ft_putstr_fd("minishell: syntax error near redirection\n", 2);
				return (-1);
			}
			// Testa se il file esiste PRIMA di creare file di output
			int test_fd = open(curr->next->value, O_RDONLY);
			if (test_fd == -1)
			{
				perror("minishell");
				return (-1);  // Fallisce PRIMA di creare output files
			}
			close(test_fd);  // Chiudi subito, riapriremo dopo
		}
		else if (curr->type == TK_HEREDOC)
		{
			if (curr->next == NULL || curr->next->type != TK_WORD)
			{
				ft_putstr_fd("minishell: syntax error near redirection\n", 2);
				return (-1);
			}
			// Per heredoc non c'è bisogno di controllare file esistenti
		}
		curr = curr->next;
	}
	
	// TERZO: Processa le redirezioni di OUTPUT (il resto del codice esistente)
	curr = tokens;
	while (curr != NULL)
	{
		if (curr->type == TK_OUT || curr->type == TK_APPEND)
		{
			if (curr->next == NULL || curr->next->type != TK_WORD)
			{
				ft_putstr_fd("minishell: syntax error near redirection\n", 2);
				if (file_fd != -1)
					close(file_fd);
				restore_input_redirection(shell);
				return -1;
			}
			filename = curr->next->value;
			if (curr->type == TK_OUT)
				flags = O_WRONLY | O_CREAT | O_TRUNC;
			else
				flags = O_WRONLY | O_CREAT | O_APPEND;
			new_fd = open(filename, flags, 0644);
			if (new_fd == -1)
			{
				perror("minishell");
				if (file_fd != -1)
					close(file_fd);
				restore_input_redirection(shell);
				return -1;
			}
			if (file_fd != -1)
				close(file_fd);
			file_fd = new_fd;
			shell->redirect_type = curr->type;
		}
		curr = curr->next;
	}
	if (file_fd != -1)
	{
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
	}
	return (0);
}

// Ripristina i file descriptor originali
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
