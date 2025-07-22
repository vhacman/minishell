/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:20:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/15 17:30:26 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** handle_cd_home - Gestisce `cd` senza argomenti.
**
** Va alla HOME usando getenv("HOME"). Se fallisce, stampa errore.
** Aggiorna OLDPWD e PWD se il cambio avviene con successo.
*/
int	handle_cd_home(t_shell *shell)
{
	char	*home;
	char	old_pwd[PATH_MAX];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (1);
	home = getenv("HOME");
	if (!home || home[0] == '\0' || chdir(home) != 0)
	{
		perror("cd");
		return (1);
	}
	update_pwd_vars(shell, old_pwd);
	return (0);
}

/*
** handle_cd_dash - Gestisce `cd -` per tornare in OLDPWD.
**
** Usa getenv("OLDPWD") e cambia directory. Stampa path su stdout.
** Aggiorna PWD e OLDPWD.
*/
int	handle_cd_dash(t_shell *shell)
{
	char	*oldpwd;
	char	old_pwd[PATH_MAX];

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
	{
		write(2, "cd: OLDPWD not set\n", 20);
		return (1);
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (1);
	if (chdir(oldpwd) != 0)
	{
		perror("cd");
		return (1);
	}
	ft_printf("%s\n", oldpwd);
	update_pwd_vars(shell, old_pwd);
	return (0);
}

/*
** handle_cd_path - Gestisce `cd <path>`, 
** inclusi ".", "..", normali o simbolici.
**
** Se path è "-", esegue il caso speciale `cd -`.
** Altrimenti prova a fare chdir, stampa errori se fallisce.
*/
int	handle_cd_path(t_shell *shell, char *path)
{
	char	old_pwd[PATH_MAX];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (1);
	if (ft_strcmp(path, "-") == 0)
		return (handle_cd_dash(shell));
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	update_pwd_vars(shell, old_pwd);
	return (0);
}

/*
** handle_cd - Entry point del builtin `cd`.
**
** args[0] = "cd", args[1] = path o NULL
**
** Se nessun argomento, chiama handle_cd_home.
** Se troppi argomenti, stampa errore con ft_putstr_fd.
** Altrimenti chiama handle_cd_path con l’argomento.
*/
int	handle_cd(char **args, t_shell *shell)
{
	if (args[1] == NULL)
		return (handle_cd_home(shell));
	if (args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (handle_cd_path(shell, args[1]));
}
