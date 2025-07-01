____________________________________________________________________________

readline

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *readline (const char *prompt);

DESCRIPTION

       readline will read a line from the terminal and return it, using
       prompt as a prompt.  If prompt is NULL or the empty string, no
       prompt is issued.  The line returned is allocated with malloc(3);
       the caller must free it when finished.  The line returned has the
       final newline removed, so only the text of the line remains.

       readline offers editing capabilities while the user is entering
       the line.  By default, the line editing commands are similar to
       those of emacs.  A vi-style line editing interface is also
       available.

       This manual page describes only the most basic use of readline.
       Much more functionality is available; see The GNU Readline Library
       and The GNU History Library for additional information.

RETURN VALUE

       readline returns the text of the line read.  A blank line returns
       the empty string.  If EOF is encountered while reading a line, and
       the line is empty, NULL is returned.  If an EOF is read with a
       non-empty line, it is treated as a newline.

____________________________________________________________________________

rl_clear_history 

void rl_clear_history (void)

DESCRIPTION

       Clear the history list by deleting all of the entries, in the same 
       manner as the History library’s clear_history() function. This differs 
       from clear_history because it frees private data Readline saves in the 
       history list.

____________________________________________________________________________

rl_on_new_line

int rl_on_new_line (void)

DESCRIPTION

       Tell the update functions that we have moved onto a new (empty) line, 
       usually after outputting a newline.

____________________________________________________________________________

l_replace_line

void rl_replace_line (const char *text, int clear_undo)

DESCRIPTION

       Replace the contents of rl_line_buffer with text. The point and mark 
       are preserved, if possible. If clear_undo is non-zero, the undo list 
       associated with the current line is cleared.

____________________________________________________________________________

rl_redisplay_function

rl_voidfunc_t * rl_redisplay_function

DESCRIPTION

       If non-zero, Readline will call indirectly through this pointer to 
       update the display with the current contents of the editing buffer. 
       By default, it is set to rl_redisplay, the default Readline 
       redisplay function (see Redisplay).

____________________________________________________________________________

add_history

void add_history (const char *string)

DESCRIPTION

       Place string at the end of the history list. The associated data 
       field (if any) is set to NULL.

____________________________________________________________________________

