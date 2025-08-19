#include "../../../include/minishell.h"

// Funzione per gestire SIGPIPE correttamente
void setup_sigpipe_handling(void)
{
    // Ignora SIGPIPE - bash non termina i processi con SIGPIPE
    signal(SIGPIPE, SIG_IGN);
}

//AGGIUNTA
int has_input_redirection(t_token *tokens)
{
	t_token *curr = tokens;
	
	while (curr)
	{
		if (curr->type == TK_IN || curr->type == TK_HEREDOC)
			return (1);
		curr = curr->next;
	}
	return (0);
}

//AGGIUNTA
int has_output_redirection(t_token *tokens)
{
	t_token *curr = tokens;
	
	while (curr)
	{
		if (curr->type == TK_OUT || curr->type == TK_APPEND)
			return (1);
		curr = curr->next;
	}
	return (0);
}
