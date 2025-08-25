# Minishell 

Autori: **Hacman Viorica Gabriela** & **Beniamino Giovannini**

> Una shell minimale in C con supporto a pipeline, redirezioni, history e
> built‑in, progettata per replicare (in parte) il comportamento di bash.

---

## Indice

* [Panoramica](#panoramica)
* [Caratteristiche principali](#caratteristiche-principali)
* [Requisiti & Build](#requisiti--build)
* [Come si usa](#come-si-usa)
* [Architettura del progetto](#architettura-del-progetto)

  * [Bootstrap & loop interattivo](#bootstrap--loop-interattivo)
  * [Lexer](#lexer)
  * [Parser](#parser)
  * [Executor](#executor)
  * [Segnali](#segnali)
  * [Built‑in](#built-in)
  * [Risoluzione del PATH](#risoluzione-del-path)
  * [Pipeline (n processi, n−1 pipe)](#pipeline-n-processi-n1-pipe)
  * [Error handling](#error-handling)
* [Struttura delle directory](#struttura-delle-directory)
* [Esempi rapidi da provare](#esempi-rapidi-da-provare)
* [Note di sviluppo](#note-di-sviluppo)
* [Crediti](#crediti)

---

## Panoramica

**Minishell** è una shell interattiva che fornisce un prompt, legge comandi
con `readline`, interpreta quoting ed espansioni, costruisce pipeline e
redirezioni e lancia processi con `execve`. Il progetto è pensato per essere
robusto sull’interattività (gestione di `Ctrl-C`/`Ctrl-D`) e fedele alle
convenzioni *bash-like* per status code, pipeline e segnali.

## Caratteristiche principali

* Prompt colorato con history e gestione *friendly* di `Ctrl-C`/`Ctrl-D`.
* Tokenizzazione con supporto a **quote singole** e **doppie**, escape selettivo
  e **concatenazione senza spazi** (es.: `foo"bar"` → `foobar`).
* Parser con **espansione variabili** (`$VAR`, `${VAR}`, `$?`, `$0`),
  validazione redirezioni e costruzione di pipeline.
* Esecuzione di **pipeline** arbitrarie, **redirezioni** (`<`, `>`, `>>`, `<<`),
  e **heredoc** con semantica dipendente dal quoting del delimitatore.
* Built‑in principali: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
* Conformità agli status code comuni: `127` comando non trovato, `126`
  permesso negato, `128+SIG` per terminazione via segnale.

## Requisiti & Build

* **C compiler** (clang/gcc), **make**.
* **readline** (con history).

Build tipica:

```bash
make        # compila minishell
make clean  # pulisce gli oggetti
make fclean # pulizia completa
make re     # ricompila da zero
```

Il binario risultante è `./minishell`.

## Come si usa

Avvia la shell:

```bash
./minishell
```

Esempio di sessione:

```text
minishell$ echo "hello" | grep hel > out.txt
minishell$ cat < out.txt
hello
minishell$ echo $?   # status dell’ultimo comando
0
```

* **Uscita**: `Ctrl-D` (EOF) su riga vuota chiude in modo pulito. `exit [n]`
  termina con status `n` (o con l’ultimo status se `n` non valido).
* **Interruzione**: `Ctrl-C` cancella la riga corrente e ridisegna il prompt.


## Architettura del progetto

### Bootstrap & loop interattivo

* `main` prepara la struttura globale `t_shell`, inizializza stato e segnali in
  *prompt mode*, quindi entra nel ciclo con `start_colored_prompt(...)`.
* Il loop costruisce il prompt, legge la riga con `readline`, completa l’input
  se ci sono quote aperte, poi passa a lexer → parser → executor. Alla fine di
  ogni giro libera le risorse temporanee.


### Lexer

* Scansione carattere per carattere con un **contesto** che traccia l’indice e
  un flag `had_whitespace` per decidere **unione** o **apertura** di un nuovo
  token.
* Riconosce: `WORD`, `PIPE` (`|`), redirezioni `<`, `>`, `>>`, `<<`, segmenti
  **quotati**. In `"..."` gestisce `\n`, `\t`, `\\`, `\"`, `\'`; in `'...'`
  il contenuto è **letterale**.
* Input multilinea: se le quote non sono chiuse, continua a leggere con un
  prompt secondario `> ` finché vengono chiuse.

### Parser

* Converte i `WORD` in **parole logiche** con espansioni: `$VAR`, `${VAR}`,
  `$?` (ultimo status), `$0` (nome programma).
* **No globbing**: `*` non escapato viene neutralizzato e poi restituito come
  `*` letterale.
* **Validazione redirezioni** prima della build: ogni operatore deve essere
  seguito da un `WORD` (filename/delimitatore). Errori → status `2`.
* Costruisce la **lista `t_cmd`**: `argv[]` e metadati I/O (IN/OUT/APPEND/
  HEREDOC). Argomenti vuoti quotati sono preservati; vuoti da espansioni non
  quotate possono essere rimossi.

### Executor

* Prepara `envp` (snapshot) da `t_env`, alloca le **pipe** (N comandi → N−1
  pipe), quindi **forka** per ciascun comando.
* Nel **figlio**: collega stdin/stdout alla pipe corretta, applica redirezioni
  (l’ultima prevale), esegue built‑in *stateless* o risolve il binario e chiama
  `execve`.
* Nel **padre**: chiude tempestivamente i fd inutili per evitare deadlock e
  attende i figli; lo **status** della pipeline è quello dell’ultimo comando.

### Segnali

* **Prompt mode**: `SIGINT` pulisce la riga (`readline`), `SIGQUIT` ignorato.
* **Executor mode**: i figli ricevono `SIGINT`/`SIGQUIT`; se un figlio termina
  per segnale → status `128 + SIG`.
* **Heredoc mode**: `SIGINT` interrompe la lettura del documento.

### Built‑in

* Eseguiti **nel padre** se unici e con effetto di stato (`cd`, `export`,
  `unset`, `exit`).
* Eseguiti **nel figlio** se in pipeline o *stateless* (`echo`, `pwd`, `env`).

### Risoluzione del PATH

* Se `argv[0]` contiene `/`: tentativo diretto. Altrimenti si itera sulle
  directory in `$PATH` con `access(X_OK)`. Se fallisce: *command not found*
  → status `127`.

### Pipeline (n processi, n−1 pipe)

Esempio:

```text
cat < in.txt | grep foo > out.txt

# figlio 1: cat        # figlio 2: grep foo
stdin ← in.txt         stdin ← pipe[0]
stdout → pipe[1]       stdout → out.txt
```

### Error handling

* Messaggi coerenti e status: `1` per errori generici I/O, `126` permessi,
  `127` comando inesistente, `2` sintassi. Decodifica `waitpid` per distinguere
  uscita normale vs segnale.

## Struttura delle directory

```
.
├── include/
├── libft/
├── src/
|   ├── clean_and_error/
|   ├── core/
|   |   ├── input
|   |   |    ├──input_handler.c
|   |   |    ├──prompt_color.c
|   |   |    └──prompt_helper.c
|   |   └── main.c
|   ├── executor/
|   |   ├── builtin/
|   |   |    ├──built_in_cd/
|   |   |    ├──built_in_env/
|   |   |    ├──built_in_exit/
|   |   |    ├──built_in_export/
|   |   |    ├──builtin_echo.c
|   |   |    ├──builtin_pwd.c
|   |   |    ├──builtin_unset.c
|   |   |    └──handle_built_in.c
|   |   ├── command_path/
|   |   |    ├──env_path_split.c
|   |   |    ├──path_search.c
|   |   |    └──path_split_utils.c
|   |   ├── pipeline/
|   |   |    ├──pipe_child_IO.c
|   |   |    ├──pipe_child_setup.c
|   |   |    ├──pipe_execution.c
|   |   |    ├──pipe_handler.c
|   |   |    ├──pipe_setup.c
|   |   |    └──pipe_utils.c
|   |   ├── prepare/
|   |   |    ├──args_convert.c
|   |   |    ├──exec_prepare.c
|   |   |    └──pipe_environment.c
|   |   ├── process/
|   |   |    ├──exec_builtins.c
|   |   |    ├──exec_dispatch.c
|   |   |    ├──fork_children.c
|   |   |    └──process_handler.c
|   |   ├── redirection/
|   |   |    ├──file_operations.c
|   |   |    ├──heredoc.c
|   |   |    ├──redir_in_setup.c
|   |   |    ├──redirection_handler.c
|   |   |    ├──redirect_input.c
|   |   |    ├──redirect_output.c
|   |   |    └──redirect_utils.c
|   |   └── signal/
|   |   |    ├──signal_setup.c
|   |   |    ├──signal_utils.c
|   |   |    └──signals.c
|   ├── lexer/
|   |   ├── escape.c
|   |   ├── token_lexer_utils.c
|   |   ├── token_redirection.c
|   |   ├── tokenizer_main.c
|   |   └── tokenizer_utils.c
|   └── parser/
|       ├── expansion/
|       ├── pipe/
|       ├── redirection/
|       ├── utils/
├──evaluation.png
├──Minishell_project_42.pdf //documentation
├── supp.supp //to sopress readline memory leaks
└── Makefile
```

## Crediti

Sviluppato da **Hacman Viorica Gabriela** & **Beniamino Giovannini** come progetto della scuola **42**.
