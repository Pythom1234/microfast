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

#pragma once
#include "types.h"

namespace Peripheral {
typedef struct {
  ptr RESERVED0[321];
  ptr OUT;
  ptr OUTSET;
  ptr OUTCLR;
  ptr IN;
  ptr DIR;
  ptr DIRSET;
  ptr DIRCLR;
  ptr LATCH;
  ptr DETECTMODE;
  ptr RESERVED1[118];
  ptr PIN_CNF[32];
} GPIO_Type;

typedef struct {
  ptr TASKS_STARTRX;
  ptr TASKS_STOPRX;
  ptr TASKS_STARTTX;
  ptr TASKS_STOPTX;
  ptr RESERVED0[3];
  ptr TASKS_SUSPEND;
  ptr RESERVED1[56];
  ptr EVENTS_CTS;
  ptr EVENTS_NCTS;
  ptr EVENTS_RXDRDY;
  ptr RESERVED2[4];
  ptr EVENTS_TXDRDY;
  ptr RESERVED3;
  ptr EVENTS_ERROR;
  ptr RESERVED4[7];
  ptr EVENTS_RXTO;
  ptr RESERVED5[46];
  ptr SHORTS;
  ptr RESERVED6[64];
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED7[93];
  ptr ERRORSRC;
  ptr RESERVED8[31];
  ptr ENABLE;
  ptr RESERVED9;
  struct {
    ptr RTS;
    ptr TXD;
    ptr CTS;
    ptr RXD;
  } PSEL;
  ptr RXD;
  ptr TXD;
  ptr RESERVED10;
  ptr BAUDRATE;
  ptr RESERVED11[17];
  ptr CONFIG;
} UART_Type;

typedef struct {
  ptr TASKS_STARTRX;
  ptr TASKS_STOPRX;
  ptr TASKS_STARTTX;
  ptr TASKS_STOPTX;
  ptr RESERVED0[7];
  ptr TASKS_FLUSHRX;
  ptr RESERVED1[52];
  ptr EVENTS_CTS;
  ptr EVENTS_NCTS;
  ptr EVENTS_RXDRDY;
  ptr RESERVED2;
  ptr EVENTS_ENDRX;
  ptr RESERVED3[2];
  ptr EVENTS_TXDRDY;
  ptr EVENTS_ENDTX;
  ptr EVENTS_ERROR;
  ptr RESERVED4[7];
  ptr EVENTS_RXTO;
  ptr RESERVED5;
  ptr EVENTS_RXSTARTED;
  ptr EVENTS_TXSTARTED;
  ptr RESERVED6;
  ptr EVENTS_TXSTOPPED;
  ptr RESERVED7[41];
  ptr SHORTS;
  ptr RESERVED8[63];
  ptr INTEN;
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED9[93];
  ptr ERRORSRC;
  ptr RESERVED10[31];
  ptr ENABLE;
  ptr RESERVED11;
  struct {
    ptr RTS;
    ptr TXD;
    ptr CTS;
    ptr RXD;
  } PSEL;
  ptr RESERVED12[3];
  ptr BAUDRATE;
  ptr RESERVED13[3];
  struct {
    ptr PTR;
    ptr MAXCNT;
    ptr AMOUNT;
  } RXD;
  ptr RESERVED14;
  struct {
    ptr PTR;
    ptr MAXCNT;
    ptr AMOUNT;
  } TXD;
  ptr RESERVED15[7];
  ptr CONFIG;
} UARTE_Type;

typedef struct {
  ptr TASKS_START;
  ptr TASKS_STOP;
  ptr RESERVED0[62];
  ptr EVENTS_VALRDY;
  ptr RESERVED1[63];
  ptr SHORTS;
  ptr RESERVED2[64];
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED3[126];
  ptr CONFIG;
  ptr VALUE;
} RNG_Type;

typedef struct {
  ptr TASKS_START;
  ptr TASKS_STOP;
  ptr TASKS_COUNT;
  ptr TASKS_CLEAR;
  ptr TASKS_SHUTDOWN;
  ptr RESERVED0[11];
  ptr TASKS_CAPTURE[6];
  ptr RESERVED1[58];
  ptr EVENTS_COMPARE[6];
  ptr RESERVED2[42];
  ptr SHORTS;
  ptr RESERVED3[64];
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED4[126];
  ptr MODE;
  ptr BITMODE;
  ptr RESERVED5;
  ptr PRESCALER;
  ptr RESERVED6[11];
  ptr CC[6];
} TIMER_Type;

typedef struct {
  ptr TASKS_START;
  ptr TASKS_SAMPLE;
  ptr TASKS_STOP;
  ptr TASKS_CALIBRATEOFFSET;
  ptr RESERVED0[60];
  ptr EVENTS_STARTED;
  ptr EVENTS_END;
  ptr EVENTS_DONE;
  ptr EVENTS_RESULTDONE;
  ptr EVENTS_CALIBRATEDONE;
  ptr EVENTS_STOPPED;
  struct {
    ptr LIMITL;
    ptr LIMITH;
  } EVENTS_CH[8];
  ptr RESERVED1[106];
  ptr INTEN;
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED2[61];
  ptr STATUS;
  ptr RESERVED3[63];
  ptr ENABLE;
  ptr RESERVED4[3];
  struct {
    ptr PSELP;
    ptr PSELN;
    ptr CONFIG;
    ptr LIMIT;
  } CH[8];
  ptr RESERVED5[24];
  ptr RESOLUTION;
  ptr OVERSAMPLE;
  ptr SAMPLERATE;
  ptr RESERVED6[12];
  struct {
    ptr PTR;
    ptr MAXCNT;
    ptr AMOUNT;
  } RESULT;
} SAADC_Type;

typedef struct {
  ptr RESERVED0;
  ptr TASKS_STOP;
  ptr TASKS_SEQSTART[2];
  ptr TASKS_NEXTSTEP;
  ptr RESERVED1[60];
  ptr EVENTS_STOPPED;
  ptr EVENTS_SEQSTARTED[2];
  ptr EVENTS_SEQEND[2];
  ptr EVENTS_PWMPERIODEND;
  ptr EVENTS_LOOPSDONE;
  ptr RESERVED2[56];
  ptr SHORTS;
  ptr RESERVED3[63];
  ptr INTEN;
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED4[125];
  ptr ENABLE;
  ptr MODE;
  ptr COUNTERTOP;
  ptr PRESCALER;
  ptr DECODER;
  ptr LOOP;
  ptr RESERVED5[2];
  struct {
    ptr PTR;
    ptr CNT;
    ptr REFRESH;
    ptr ENDDELAY;
    ptr RESERVED[4];
  } SEQ[2];
  struct {
    ptr OUT[4];
  } PSEL;
} PWM_Type;

typedef struct {
  ptr TASKS_START;
  ptr TASKS_STOP;
  ptr RESERVED0[62];
  ptr EVENTS_DATARDY;
  ptr RESERVED1[128];
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED2[127];
  ptr TEMP;
  ptr RESERVED3[5];
  ptr A0;
  ptr A1;
  ptr A2;
  ptr A3;
  ptr A4;
  ptr A5;
  ptr RESERVED4[2];
  ptr B0;
  ptr B1;
  ptr B2;
  ptr B3;
  ptr B4;
  ptr B5;
  ptr RESERVED5[2];
  ptr T0;
  ptr T1;
  ptr T2;
  ptr T3;
  ptr T4;
} TEMP_Type;

typedef struct {
  ptr TASKS_STARTRX;
  ptr RESERVED0;
  ptr TASKS_STARTTX;
  ptr RESERVED1[2];
  ptr TASKS_STOP;
  ptr RESERVED2;
  ptr TASKS_SUSPEND;
  ptr TASKS_RESUME;
  ptr RESERVED3[56];
  ptr EVENTS_STOPPED;
  ptr RESERVED4[7];
  ptr EVENTS_ERROR;
  ptr RESERVED5[8];
  ptr EVENTS_SUSPENDED;
  ptr EVENTS_RXSTARTED;
  ptr EVENTS_TXSTARTED;
  ptr RESERVED6[2];
  ptr EVENTS_LASTRX;
  ptr EVENTS_LASTTX;
  ptr RESERVED7[39];
  ptr SHORTS;
  ptr RESERVED8[63];
  ptr INTEN;
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED9[110];
  ptr ERRORSRC;
  ptr RESERVED10[14];
  ptr ENABLE;
  ptr RESERVED11;
  struct {
    ptr SCL;
    ptr SDA;
  } PSEL;
  ptr RESERVED12[5];
  ptr FREQUENCY;
  ptr RESERVED13[3];
  struct {
    ptr PTR;
    ptr MAXCNT;
    ptr AMOUNT;
    ptr LIST;
  } RXD;
  struct {
    ptr PTR;
    ptr MAXCNT;
    ptr AMOUNT;
    ptr LIST;
  } TXD;
  ptr RESERVED14[13];
  ptr ADDRESS;
} TWIM_Type;

typedef struct {
  ptr TASKS_STARTRX;
  ptr RESERVED0;
  ptr TASKS_STARTTX;
  ptr RESERVED1[2];
  ptr TASKS_STOP;
  ptr RESERVED2;
  ptr TASKS_SUSPEND;
  ptr TASKS_RESUME;
  ptr RESERVED3[56];
  ptr EVENTS_STOPPED;
  ptr EVENTS_RXDREADY;
  ptr RESERVED4[4];
  ptr EVENTS_TXDSENT;
  ptr RESERVED5;
  ptr EVENTS_ERROR;
  ptr RESERVED6[4];
  ptr EVENTS_BB;
  ptr RESERVED7[3];
  ptr EVENTS_SUSPENDED;
  ptr RESERVED8[45];
  ptr SHORTS;
  ptr RESERVED9[64];
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED10[110];
  ptr ERRORSRC;
  ptr RESERVED11[14];
  ptr ENABLE;
  ptr RESERVED12;
  struct {
    ptr SCL;
    ptr SDA;
  } PSEL;
  ptr RESERVED13[2];
  ptr RXD;
  ptr TXD;
  ptr RESERVED14;
  ptr FREQUENCY;
  ptr RESERVED15[24];
  ptr ADDRESS;
} TWI_Type;

typedef struct {
  ptr TASKS_TXEN;
  ptr TASKS_RXEN;
  ptr TASKS_START;
  ptr TASKS_STOP;
  ptr TASKS_DISABLE;
  ptr TASKS_RSSISTART;
  ptr TASKS_RSSISTOP;
  ptr TASKS_BCSTART;
  ptr TASKS_BCSTOP;
  ptr TASKS_EDSTART;
  ptr TASKS_EDSTOP;
  ptr TASKS_CCASTART;
  ptr TASKS_CCASTOP;
  ptr RESERVED0[51];
  ptr EVENTS_READY;
  ptr EVENTS_ADDRESS;
  ptr EVENTS_PAYLOAD;
  ptr EVENTS_END;
  ptr EVENTS_DISABLED;
  ptr EVENTS_DEVMATCH;
  ptr EVENTS_DEVMISS;
  ptr EVENTS_RSSIEND;
  ptr RESERVED1[2];
  ptr EVENTS_BCMATCH;
  ptr RESERVED2;
  ptr EVENTS_CRCOK;
  ptr EVENTS_CRCERROR;
  ptr EVENTS_FRAMESTART;
  ptr EVENTS_EDEND;
  ptr EVENTS_EDSTOPPED;
  ptr EVENTS_CCAIDLE;
  ptr EVENTS_CCABUSY;
  ptr EVENTS_CCASTOPPED;
  ptr EVENTS_RATEBOOST;
  ptr EVENTS_TXREADY;
  ptr EVENTS_RXREADY;
  ptr EVENTS_MHRMATCH;
  ptr RESERVED3[2];
  ptr EVENTS_SYNC;
  ptr EVENTS_PHYEND;
  ptr EVENTS_CTEPRESENT;
  ptr RESERVED4[35];
  ptr SHORTS;
  ptr RESERVED5[64];
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED6[61];
  ptr CRCSTATUS;
  ptr RESERVED7;
  ptr RXMATCH;
  ptr RXCRC;
  ptr DAI;
  ptr PDUSTAT;
  ptr RESERVED8[13];
  ptr CTESTATUS;
  ptr RESERVED9[2];
  ptr DFESTATUS;
  ptr RESERVED10[42];
  ptr PACKETPTR;
  ptr FREQUENCY;
  ptr TXPOWER;
  ptr MODE;
  ptr PCNF0;
  ptr PCNF1;
  ptr BASE0;
  ptr BASE1;
  ptr PREFIX0;
  ptr PREFIX1;
  ptr TXADDRESS;
  ptr RXADDRESSES;
  ptr CRCCNF;
  ptr CRCPOLY;
  ptr CRCINIT;
  ptr RESERVED11;
  ptr TIFS;
  ptr RSSISAMPLE;
  ptr RESERVED12;
  ptr STATE;
  ptr DATAWHITEIV;
  ptr RESERVED13[2];
  ptr BCC;
  ptr RESERVED14[39];
  ptr DAB[8];
  ptr DAP[8];
  ptr DACNF;
  ptr MHRMATCHCONF;
  ptr MHRMATCHMAS;
  ptr RESERVED15;
  ptr MODECNF0;
  ptr RESERVED16[3];
  ptr SFD;
  ptr EDCNT;
  ptr EDSAMPLE;
  ptr CCACTRL;
  ptr RESERVED17[164];
  ptr DFEMODE;
  ptr CTEINLINECONF;
  ptr RESERVED18[2];
  ptr DFECTRL1;
  ptr DFECTRL2;
  ptr RESERVED19[4];
  ptr SWITCHPATTERN;
  ptr CLEARPATTERN;
  struct {
    ptr DFEGPIO[8];
  } PSEL;
  struct {
    ptr PTR;
    ptr MAXCNT;
    ptr AMOUNT;
  } DFEPACKET;
  ptr RESERVED20[424];
  ptr POWER;
} RADIO_Type;

typedef struct {
  ptr TASKS_HFCLKSTART;
  ptr TASKS_HFCLKSTOP;
  ptr TASKS_LFCLKSTART;
  ptr TASKS_LFCLKSTOP;
  ptr TASKS_CAL;
  ptr TASKS_CTSTART;
  ptr TASKS_CTSTOP;
  ptr RESERVED0[57];
  ptr EVENTS_HFCLKSTARTED;
  ptr EVENTS_LFCLKSTARTED;
  ptr RESERVED1;
  ptr EVENTS_DONE;
  ptr EVENTS_CTTO;
  ptr RESERVED2[5];
  ptr EVENTS_CTSTARTED;
  ptr EVENTS_CTSTOPPED;
  ptr RESERVED3[117];
  ptr INTENSET;
  ptr INTENCLR;
  ptr RESERVED4[63];
  ptr HFCLKRUN;
  ptr HFCLKSTAT;
  ptr RESERVED5;
  ptr LFCLKRUN;
  ptr LFCLKSTAT;
  ptr LFCLKSRCCOPY;
  ptr RESERVED6[62];
  ptr LFCLKSRC;
  ptr RESERVED7[3];
  ptr HFXODEBOUNCE;
  ptr LFXODEBOUNCE;
  ptr RESERVED8[2];
  ptr CTIV;
  ptr RESERVED9[8];
  ptr TRACECONFIG;
} CLOCK_Type;

GPIO_Type* const P0 = (GPIO_Type*)0x50000000;
GPIO_Type* const P1 = (GPIO_Type*)0x50000300;
UART_Type* const UART = (UART_Type*)0x40002000;
UARTE_Type* const UARTE0 = (UARTE_Type*)0x40002000;
UARTE_Type* const UARTE1 = (UARTE_Type*)0x40028000;
RNG_Type* const RNG = (RNG_Type*)0x4000D000;
TIMER_Type* const TIMER0 =
    (TIMER_Type*)0x40008000; // timer for `wait` functions TODO!
TIMER_Type* const TIMER1 =
    (TIMER_Type*)0x40009000; // timer for timeout (eg. uart::read())
TIMER_Type* const TIMER2 =
    (TIMER_Type*)0x4000A000; // timer for all time from start TODO!
TIMER_Type* const TIMER3 = (TIMER_Type*)0x4001A000;
TIMER_Type* const TIMER4 = (TIMER_Type*)0x4001B000;
CLOCK_Type* const CLOCK = (CLOCK_Type*)0x40000000;
SAADC_Type* const SAADC = (SAADC_Type*)0x40007000;
PWM_Type* const PWM0 = (PWM_Type*)0x4001C000;
PWM_Type* const PWM1 = (PWM_Type*)0x40021000;
PWM_Type* const PWM2 = (PWM_Type*)0x40022000;
PWM_Type* const PWM3 = (PWM_Type*)0x4002D000;
TEMP_Type* const TEMP = (TEMP_Type*)0x4000C000;
TWIM_Type* const TWIM0 = (TWIM_Type*)0x40003000; // external i2c
TWIM_Type* const TWIM1 = (TWIM_Type*)0x40004000; // internal i2c
TWI_Type* const TWI0 = (TWI_Type*)0x40003000;
TWI_Type* const TWI1 = (TWI_Type*)0x40004000;
RADIO_Type* const RADIO = (RADIO_Type*)0x40001000;

GPIO_Type* const P[2] = {P0, P1};
UARTE_Type* const UARTE[2] = {UARTE0, UARTE1};
TIMER_Type* const TIMER[5] = {TIMER0, TIMER1, TIMER2, TIMER3, TIMER4};
PWM_Type* const PWM[4] = {PWM0, PWM1, PWM2, PWM3};
TWIM_Type* const TWIM[2] = {TWIM0, TWIM1};
TWI_Type* const TWI[2] = {TWI0, TWI1};

} // namespace Peripheral

enum Pin {
  PIN_0 = 2,
  PIN_1 = 3,
  PIN_2 = 4,
  PIN_3 = 31,
  PIN_4 = 28,
  PIN_5 = 14,
  PIN_6 = 37,
  PIN_7 = 11,
  PIN_8 = 10,
  PIN_9 = 9,
  PIN_10 = 30,
  PIN_11 = 23,
  PIN_12 = 12,
  PIN_13 = 17,
  PIN_14 = 1,
  PIN_15 = 13,
  PIN_16 = 34,
  PIN_19 = 26,
  PIN_20 = 32,

  BUTTON_A = 14,
  BUTTON_B = 23,
  LOGO = 36,

  RUN_MIC = 20,
  MIC_IN = 5,
  SPEAKER = 0,

  UART_TX = 6,
  UART_RX = 40,

  I2C_INT_SCL = 8,
  I2C_INT_SDA = 16,
  SENSOR_DATA_READY = 25,
  I2C_SCL = 26,
  I2C_SDA = 32,

  SPI_MOSI = 13,
  SPI_MISO = 1,
  SPI_SCK = 17,

  ROW_1 = 21,
  ROW_2 = 22,
  ROW_3 = 15,
  ROW_4 = 24,
  ROW_5 = 19,

  COL_1 = 28,
  COL_2 = 11,
  COL_3 = 31,
  COL_4 = 37,
  COL_5 = 30,
};
