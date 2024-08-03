/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/*
With help from: https://github.com/zhmu
*/
.text

.globl  _start
.type   _start,@function

_start:
        movq    %rsp,%rbp
        movq    0(%rbp),%rdi        /* argc */
        leaq    8(%rbp),%rsi        /* argv */
        leaq    8(%rsi,%rdi,8),%rdx /* envp */

        andq    $~15,%rsp
        call    main
        movq    %rax,%rdi
        call    _exit

        /* force an illegal opcode exception if _exit returns */
        ud2

.globl  syscall6
.type   syscall6,@function

syscall6:
        /* convert arguments as passed by ELF ABI to Linux syscall ABI */
        movq    %rdi, %rax  /* number */
        movq    %rsi, %rdi  /* arg0 */
        movq    %rdx, %rsi  /* arg1 */
        movq    %rcx, %rdx  /* arg2 */
        /* arg4 is already in %r8, arg5 is already in %r9 */
        syscall
        andq    %rax,%rax
        js      1f

        /* No error; result is in %rax */
        retq

1:      /* Move error number to errno and return -1 */
        negq    %rax
        movq    %rax, PC_bare_errno
        movq    $-1, %rax
        retq
