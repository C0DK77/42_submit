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

getcwd

#include <unistd.h>

char *getcwd(char *buf, size_t size);

DESCRIPTION

       The getcwd() function copies the absolute pathname of the current 
       working directory into the memory referenced by buf and returns a 
       pointer to buf.  The size argument is the size, in bytes, of the
       array referenced by buf.

       If buf is NULL, space is allocated as necessary to store the 
       pathname and size is ignored.  This space may later be free(3)'d.

       The function getwd() is a compatibility routine which calls getcwd() 
       with its buf argument and a size of MAXPATHLEN (as defined in the 
       include file <sys/param.h>).  Obviously, buf should be at least
       MAXPATHLEN bytes in length.

       These routines have traditionally been used by programs to save the 
       name of a working directory for the purpose of returning to it.  A 
       much faster and less error-prone method of accomplishing this is to 
       open the current directory (‘.’) and use the fchdir(2) function to 
       return.

RETURN VALUES

       Upon successful completion, a pointer to the pathname is returned.  
       Otherwise a NULL pointer is returned and the global variable errno 
       is set to indicate the error.  In addition, getwd() copies the
       error message associated with errno into the memory referenced by buf.

ERRORS

       The getcwd() function will fail if:

       [EINVAL]             The size argument is zero.

       [ENOENT]             A component of the pathname no longer exists.

       [ENOMEM]             Insufficient memory is available.

       [ERANGE]             The size argument is greater than zero but
                            smaller than the length of the pathname plus 1.

       The getcwd() function may fail if:

       [EACCES]             Read or search permission was denied for a 
                            component of the pathname.  This is only 
                            checked in limited cases, depending on 
                            implementation details.

____________________________________________________________________________

getenv

#include <stdlib.h>

char *getenv(const char *name);

DESCRIPTION

       These functions set, unset and fetch environment variables from the host
       environment list.

       The getenv() function obtains the current value of the environment 
       variable, name.  The application should not modify the string pointed to
       by the getenv() function.

RETURN VALUES

       The getenv() function returns the value of the environment variable as a
       NUL-terminated string.  If the variable name is not in the current 
       environment, NULL is returned.

ERRORS

     [EINVAL]               The function getenv(), setenv() or unsetenv() failed 
                            because the name is a NULL pointer, points to an empty
                            string, or points to a string containing an “=” character.

____________________________________________________________________________
