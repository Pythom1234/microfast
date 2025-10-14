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

#include "peripheral.h"
#include "types.h"

static u32* sp;

static void msg(const char* str) {
  Peripheral::UART->ENABLE = 0x4;
  Peripheral::UART->BAUDRATE = 0x01D7E000;
  Peripheral::UART->PSEL.TXD = 0x00000006;
  Peripheral::UART->TASKS_STARTTX = 0x1;
  for (int i = 0; str[i] != '\0'; i++) {
    Peripheral::UART->EVENTS_TXDRDY = 0x0;
    Peripheral::UART->TXD = str[i];
    while (!Peripheral::UART->EVENTS_TXDRDY)
      ;
  }
  Peripheral::UART->TASKS_STOPTX = 0x1;
  Peripheral::UART->ENABLE = 0x0;
}

static const char* itoa(u32 v) {
  static char buf[9];
  for (int i = 0; i < 8; i++) {
    int nibble = (v >> ((7 - i) * 4)) & 0xF;
    buf[i] = (nibble < 10) ? '0' + nibble : 'A' + (nibble - 10);
  }
  buf[8] = '\0';
  return buf;
}

static void print_reg() {
  msg("\033[1;32mR0\033[0m:  0x");
  msg(itoa(sp[0]));
  msg("\n\r\033[1;32mR1\033[0m:  0x");
  msg(itoa(sp[1]));
  msg("\n\r\033[1;32mR2\033[0m:  0x");
  msg(itoa(sp[2]));
  msg("\n\r\033[1;32mR3\033[0m:  0x");
  msg(itoa(sp[3]));
  msg("\n\r\033[1;32mR12\033[0m: 0x");
  msg(itoa(sp[4]));
  msg("\n\r\033[1;32mLR\033[0m:  0x");
  msg(itoa(sp[5]));
  msg("\n\r\033[1;32mPC\033[0m:  0x");
  msg(itoa(sp[6]));
  msg("\n\r\033[1;32mPSR\033[0m: 0x");
  msg(itoa(sp[7]));
  msg("\n\r");
}

extern "C" {
__attribute__((weak)) void __afterfault() {
  while (1)
    ;
}
IRQ void __init() {
  Peripheral::CLOCK->EVENTS_HFCLKSTARTED = 0;
  Peripheral::CLOCK->TASKS_HFCLKSTART = 1;
  while (Peripheral::CLOCK->EVENTS_HFCLKSTARTED == 0)
    ;
  Peripheral::CLOCK->EVENTS_LFCLKSTARTED = 0;
  Peripheral::CLOCK->TASKS_LFCLKSTART = 1;
  while (Peripheral::CLOCK->EVENTS_LFCLKSTARTED == 0)
    ;
  Peripheral::TIMER2->BITMODE = 0x3;
  Peripheral::TIMER2->TASKS_START = 0x1;
  Peripheral::RTC2->PRESCALER = 0xFFF;
  Peripheral::RTC2->TASKS_START = 0x1;
}

IRQ void __nmi() {
  asm volatile("tst lr, #4\n"
               "ite eq\n"
               "mrseq %0, msp\n"
               "mrsne %0, psp\n"
               : "=r"(sp));
  msg("\n\r------\n\r\033[1;34;4mNonMaskableInterrupt\033[0m\n\r");
  print_reg();
  msg("------\n\r\n\r");
  __afterfault();
}
// TODO: zmenit 0xE000ED2C atd. na Peripheral::...
IRQ void __hardfault() {
  asm volatile("tst lr, #4\n"
               "ite eq\n"
               "mrseq %0, msp\n"
               "mrsne %0, psp\n"
               : "=r"(sp));
  msg("\n\r------\n\r\033[1;31;4mHardFault\033[0m\n\r");
  if (*(ptr)0xE000ED2C & 1 << 30)
    msg("\033[1;31mHardFault\033[0m: Fault escalated to a hard fault\n\r");
  if (*(ptr)0xE000ED2C & 1 << 1)
    msg("\033[1;31mHardFault\033[0m: Bus error on a vector read\n\r");
  print_reg();
  msg("------\n\r\n\r");
  __afterfault();
}
IRQ void __memfault() {
  asm volatile("tst lr, #4\n"
               "ite eq\n"
               "mrseq %0, msp\n"
               "mrsne %0, psp\n"
               : "=r"(sp));
  msg("\n\r------\n\r\033[1;35;4mMemManageFault\033[0m\n\r");
  if (*(ptr)0xE000ED28 & 1 << 7) {
    u32 v = *(ptr)0xE000ED34;
    msg("\033[1;35mMemManageFault\033[0m: at address 0x");
    msg(itoa(v));
    msg("\n\r");
  }
  if (*(ptr)0xE000ED28 & 1 << 5)
    msg("\033[1;35mMemManageFault\033[0m: MPU or default memory map mismatch "
        "during lazy floating-point state preservation\n\r");
  if (*(ptr)0xE000ED28 & 1 << 4)
    msg("\033[1;35mMemManageFault\033[0m: MPU or default memory map mismatch "
        "during exception stacking\n\r");
  if (*(ptr)0xE000ED28 & 1 << 3)
    msg("\033[1;35mMemManageFault\033[0m: MPU or default memory map mismatch "
        "during exception unstacking\n\r");
  if (*(ptr)0xE000ED28 & 1 << 1)
    msg("\033[1;35mMemManageFault\033[0m: MPU or default memory map mismatch "
        "on data access\n\r");
  if (*(ptr)0xE000ED28 & 1 << 0)
    msg("\033[1;35mMemManageFault\033[0m: MPU or default memory map mismatch "
        "on instruction access\n\r");
  print_reg();
  msg("------\n\r\n\r");
  __afterfault();
}
IRQ void __busfault() {
  asm volatile("tst lr, #4\n"
               "ite eq\n"
               "mrseq %0, msp\n"
               "mrsne %0, psp\n"
               : "=r"(sp));
  msg("\n\r------\n\r\033[1;36;4mBusFault\033[0m\n\r");
  if (*(ptr)0xE000ED29 & 1 << 7) {
    u32 v = *(ptr)0xE000ED38;
    msg("\033[1;36mBusFault\033[0m: At address 0x");
    msg(itoa(v));
    msg("\n\r");
  }
  if (*(ptr)0xE000ED29 & 1 << 5)
    msg("\033[1;36mBusFault\033[0m: Bus error during lazy floating-point "
        "state "
        "preservation\n\r");
  if (*(ptr)0xE000ED29 & 1 << 4)
    msg("\033[1;36mBusFault\033[0m: Bus error during exception stacking\n\r");
  if (*(ptr)0xE000ED29 & 1 << 3)
    msg("\033[1;36mMemManageFault\033[0m: Bus error during exception "
        "unstacking\n\r");
  if (*(ptr)0xE000ED29 & 1 << 2)
    msg("\033[1;36mBusFault\033[0m: Imprecise data bus error\n\r");
  if (*(ptr)0xE000ED29 & 1 << 1)
    msg("\033[1;36mBusFault\033[0m: Precise data bus error\n\r");
  if (*(ptr)0xE000ED29 & 1 << 0)
    msg("\033[1;36mBusFault\033[0m: Bus error during instruction "
        "prefetch\n\r");
  print_reg();
  msg("------\n\r\n\r");
  __afterfault();
}
IRQ void __usagefault() {
  asm volatile("tst lr, #4\n"
               "ite eq\n"
               "mrseq %0, msp\n"
               "mrsne %0, psp\n"
               : "=r"(sp));
  msg("\n\r------\n\r\033[1;33;4mUsageFault\033[0m\n\r");
  if (*(ptr)0xE000ED2A & 1 << 9)
    msg("\033[1;33mUsageFault\033[0m: Divide by 0\n\r");
  if (*(ptr)0xE000ED2A & 1 << 8)
    msg("\033[1;33mUsageFault\033[0m: Illegal unaligned load or store\n\r");
  if (*(ptr)0xE000ED2A & 1 << 3)
    msg("\033[1;33mUsageFault\033[0m: Attempt to access a coprocessor\n\r");
  if (*(ptr)0xE000ED2A & 1 << 2)
    msg("\033[1;33mUsageFault\033[0m: Invalid EXC_RETURN value\n\r");
  if (*(ptr)0xE000ED2A & 1 << 1)
    msg("\033[1;33mUsageFault\033[0m: Attempt to enter an invalid "
        "instruction "
        "set state\n\r");
  if (*(ptr)0xE000ED2A & 1 << 0)
    msg("\033[1;33mUsageFault\033[0m: Undefined instruction\n\r");
  print_reg();
  msg("------\n\r\n\r");
  __afterfault();
}
}
