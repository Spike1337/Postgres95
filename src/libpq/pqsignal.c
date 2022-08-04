/*-------------------------------------------------------------------------
 *
 * pqsignal.c--
 *    reliable BSD-style signal(2) routine stolen from RWW who stole it
 *    from Stevens...
 *
 * Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *    $Header: /usr/local/cvsroot/postgres95/src/libpq/pqsignal.c,v 1.1.1.1 1996/07/09 06:22:17 scrappy Exp $
 *
 * NOTES
 *	This shouldn't be in libpq, but the monitor and some other
 *	things need it...
 *
 *-------------------------------------------------------------------------
 */
#include "libpq/pqsignal.h"

pqsigfunc
pqsignal(int signo, pqsigfunc func)
{
#if defined(USE_POSIX_SIGNALS)
    struct sigaction act, oact;
    
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo != SIGALRM) {
	act.sa_flags |= SA_RESTART;
    }
    if (sigaction(signo, &act, &oact) < 0)
	return(SIG_ERR);
    return(oact.sa_handler);
#else /* !USE_POSIX_SIGNALS */
    exit(1); /* this should never be reached, pqsignal should only
	      be called if USE_POSIX_SIGNALS is true*/
#endif /* !USE_POSIX_SIGNALS */
}
