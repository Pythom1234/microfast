/*
 * This file is part of Micro:fast.
 *
 * Copyright (C) 2025 Pythom1234
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see
 * <http://www.gnu.org/licenses/>.
 */

 .syntax unified

.global __reset

.section .vectors

.word __stack
.word __reset
.word __nmi
.word __hardfault
.word __memfault
.word __busfault
.word __usagefault

.section .text

.thumb_func
__reset:
    // Null RAM
    ldr r0, =0x20000000
    ldr r1, =0x20020000
    mov r2, #0
1:  cmp r0, r1
    itt lt
    strlt r2, [r0], #4
    blt 1b

    // Copy .data
    ldr r0, =__sidata
    ldr r1, =__sdata
    ldr r2, =__edata
1:  cmp r1, r2
    itt lt
    ldrlt r3, [r0], #4
    strlt r3, [r1], #4
    blt 1b

    // Null .bss
    ldr r0, =__sbss
    ldr r1, =__ebss
    mov r2, #0
1:  cmp r0, r1
    itt lt
    strlt r2, [r0], #4
    blt 1b

    // Enable FPU
    ldr r0, =0xE000ED88
    ldr r1, =0x00F00000
    str r1, [r0]

    // Enable interrupts
    ldr r0, =0xE000ED24
    ldr r1, =0x00070000
    str r1, [r0]

    // Start program
    bl main
    // Halt at end
    b .
