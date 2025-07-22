/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:20:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/02/24 23:00:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*ENG: Extracts a line from the input buffer up to and including the
 	newline (\n),
 * if present. 
 * If there is no newline, extracts the entire row to the end of the buffer. 
 * Updates the original buffer pointer to point to the remaining data.
 * Returns the extracted line or NULL in case of error or empty buffer. 
 * The returned string must be freed by the caller. */

char	*extract_line(char **raw_input_ptr)
{
	char			*line;
	t_buffer_info	data;
	size_t			line_len;

	if (!raw_input_ptr || !*raw_input_ptr || !**raw_input_ptr)
		return (NULL);
	data.raw_input = *raw_input_ptr;
	data.raw_input_ptr = raw_input_ptr;
	data.end = ft_strchr(data.raw_input, '\n');
	data.remainder = NULL;
	if (data.end)
		line_len = data.end - data.raw_input + 1;
	else
		line_len = ft_strlen(data.raw_input);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	ft_strncpy(line, data.raw_input, line_len);
	line[line_len] = '\0';
	extract_line_helper(data, line);
	return (line);
}

/* Gestisce il buffer dopo l'estrazione di una riga. 
 * Si occupa di liberare il buffer originale, aggiornare il puntatore 
 * per i dati rimanenti e gestire il testo dopo il newline (se presente). 
 * Se c'è testo rimanente, viene duplicato in un nuovo buffer
 * e il puntatore aggiornato. Se non c'è testo rimanente
 * o se non c'è un newline, il puntatore viene impostato a NULL. 
 * La riga estratta viene liberata in caso
 * di errore nell'allocazione del remainder.*/
void	extract_line_helper(t_buffer_info data, char *line)
{
	if (data.end && *(data.end + 1))
	{
		data.remainder = ft_strdup(data.end + 1);
		if (!data.remainder)
			free(line);
		free(data.raw_input);
		*(data.raw_input_ptr) = data.remainder;
	}
	else
	{
		free(data.raw_input);
		*(data.raw_input_ptr) = NULL;
	}
}

/* Legge dati da un file descriptor e aggiorna il buffer di input.
 * Se il buffer esiste, i dati vengono concatenati, altrimenti viene 
 * creato un nuovo buffer. Ritorna il buffer aggiornato o NULL
 * in caso di errore o EOF. Libera il buffer originale 
 * se non ci sono errori.*/
char	*read_and_update(int fd, char *raw_input_data)
{
	char	*buffer;
	char	*new_buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (free(buffer), NULL);
	if (bytes_read == 0)
		return (free(buffer), raw_input_data);
	buffer[bytes_read] = '\0';
	if (!raw_input_data)
		new_buffer = ft_strdup(buffer);
	else
		new_buffer = ft_strjoin(raw_input_data, buffer);
	free(buffer);
	free(raw_input_data);
	return (new_buffer);
}

/* Legge dati da un file descriptor fino a trovare un newline o EOF.
 * Continua a leggere finché non trova un newline o la fine del 
 * file, utilizzando read_and_update per leggere i dati.
 * Ritorna il buffer con i dati letti o NULL in caso di errore.*/
char	*get_next_line_reader(int fd, char *raw_input_data)
{
	char	*read_done;

	while (!raw_input_data || !ft_strchr(raw_input_data, '\n'))
	{
		read_done = read_and_update(fd, raw_input_data);
		if (!read_done)
		{
			if (raw_input_data)
				free(raw_input_data);
			raw_input_data = NULL;
			return (NULL);
		}
		if (read_done == raw_input_data
			&& !ft_strchr(raw_input_data, '\n'))
			break ;
		raw_input_data = read_done;
	}
	return (raw_input_data);
}

/* Legge una riga da un file descriptor e la restituisce come 
 * stringa terminata da null. Usa raw_input_data per mantenere 
 * i dati tra le chiamate, legge con get_next_line_reader e 
 * estrae la riga con extract_line. Ritorna NULL in caso 
 * di errore, EOF o se i parametri sono invalidi.*/
char	*get_next_line(int fd)
{
	static char	*raw_input_data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	raw_input_data = get_next_line_reader(fd, raw_input_data);
	if (!raw_input_data || !*raw_input_data)
	{
		if (raw_input_data)
		{
			free(raw_input_data);
			raw_input_data = NULL;
		}
		return (NULL);
	}
	line = extract_line(&raw_input_data);
	return (line);
}
