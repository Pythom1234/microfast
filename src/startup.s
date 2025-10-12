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
.word 0
.word 0
.word 0
.word 0
.word __svcall
.word 0
.word 0
.word __pendsv
.word __systick

// Interrupts
.word __power_clock
.word __radio
.word __uarte0_uart0
.word __spim0_spis0_twim0_twis0_spi0_twi0
.word __spim1_spis1_twim1_twis1_spi1_twi1
.word __nfct
.word __gpiote
.word __saadc
.word __timer0
.word __timer1
.word __timer2
.word __rtc0
.word __temp
.word __rng
.word __ecb
.word __ccm_aar
.word __wdt
.word __rtc1
.word __qdec
.word __comp_lpcomp
.word __swi0_egu0
.word __swi1_egu1
.word __swi2_egu2
.word __swi3_egu3
.word __swi4_egu4
.word __swi5_egu5
.word __timer3
.word __timer4
.word __pwm0
.word __pdm
.word __mwu
.word __pwm1
.word __pwm2
.word __spim2_spis2_spi2
.word __rtc2
.word __i2s
.word __fpu
.word __usbd
.word __uarte1
.word __pwm3
.word __spim3

.section .startup, "ax"

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

    // Initialize
    bl __init
    // Start program
    bl main
    // Halt at end
    b .
