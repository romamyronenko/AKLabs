.syntax unified
.cpu cortex-m4
//.fpu softvfp
.thumb
//global memory locations
.global vtable_kernel
.global __kernel_reset__

.type vtable_kernel, %object
.type __kernel_reset__, %function

.section .interrupt_vector
vtable_kernel:
	.word __stack_start
	.word __kernel_reset__+1
	.size vtable_kernel, .-vtable_kernel

.section .rodata
	start: .asciz "kernel start\n"
	finish: .asciz "value in reg #1: "

.section .text
__kernel_reset__:
	ldr r0, =start
	bl dbgput_line
	//calculating
	mov r0, #3    
	mov r1, #2    
	mov r2, #3  
	mul r3, r0, r1
	cmp r3, #10
	ITE GE
	orrGE r4, r0, r1
	andLT r4, r0, r1
	mul r5, r4, r2  
	ldr r0, =finish
	bl dbgput
        mov r0, r5
        bl dbgput_num
        end:
		b end
