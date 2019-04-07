/* Signal handlers. */
#include <stdio.h>

#include "utils.h"

void ignore_signal(int signum)
{
    /* print debug information */
    if (DEBUG) fprintf(stderr, "Warning: Caught %d\n", signum);
}
