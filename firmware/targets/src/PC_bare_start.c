/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/*
Adapted from https://github.com/lpsantil/rt0
*/

#include <PC_bare_rt0.h>

/* pointer to array of char* strings that define the current environment variables */
char **__environ;
int PC_bare_errno;
