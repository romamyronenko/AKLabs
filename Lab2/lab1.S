.global lab1
.syntax unified
#define A #11
#define B #1
#define C #2
lab1:
    push {lr}
    mov r0, B
    mov r1, A
    mov r2, C
    bl calc
    pop {pc}
calc:
    push { r4, r5, lr }
    sub r3, r0, r1
    cmp r3, #0
    it ge
    addge r3, r1, r0

    sdiv r3, r2
    pop { r4, r5, lr }
