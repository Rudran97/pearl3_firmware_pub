    .file   "end.S"
    .option nopic
    .attribute arch, "rv32i2p0"

    .text
    .align  4
    .globl  _Exit
    .type   _Exit, @function

_Exit:
.L2:
    j   .L2

