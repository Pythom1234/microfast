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

#include "microbit.h"
#include "peripheral.h"
#include <cmath>
#include <cstdlib>
#include <cstring>

static void msg(const char* str) { // TODO: remove (debug)
  *(ptr*)0x40002500 = 0x4;
  *(ptr*)0x40002524 = 0x01D7E000;
  *(ptr*)0x4000250C = 0x00000006;
  *(ptr*)0x40002008 = 0x1;
  for (int i = 0; str[i] != '\0'; i++) {
    *(ptr*)0x4000211C = 0x0;
    *(ptr*)0x4000251C = str[i];
    while (!*(ptr*)0x4000211C)
      ;
  }
  *(ptr*)0x4000200C = 0x1;
  *(ptr*)0x40002500 = 0x0;
}

namespace microbit {
namespace uart {
void setBaudrate(BaudRate baudrate) {
  Peripheral::UART->BAUDRATE = baudrate;
}
void startTX() {
  Peripheral::UART->ENABLE = 0x4;
  Peripheral::UART->TASKS_STOPTX = 0x1;
  Peripheral::UART->PSEL.TXD = Pin::UART_TX;
  // Peripheral::UART->BAUDRATE = 0x01D7E000; // 115200 baud
  Peripheral::UART->TASKS_STARTTX = 0x1;
}
void stopTX() {
  Peripheral::UART->TASKS_STOPTX = 0x1;
  Peripheral::UART->PSEL.TXD = 0xFFFFFFFF;
  Peripheral::UART->ENABLE = 0x0;
}
void startRX() {
  Peripheral::UART->ENABLE = 0x4;
  Peripheral::UART->TASKS_STOPRX = 0x1;
  Peripheral::UART->PSEL.RXD = Pin::UART_RX;
  Peripheral::UART->EVENTS_RXDRDY = 0x0;
  // Peripheral::UART->BAUDRATE = 0x01D7E000; // 115200 baud
  Peripheral::UART->TASKS_STARTRX = 0x1;
}
void stopRX() {
  Peripheral::UART->TASKS_STOPRX = 0x1;
  Peripheral::UART->PSEL.RXD = 0xFFFFFFFF;
  Peripheral::UART->ENABLE = 0x0;
}
void write(char byte) {
  Peripheral::UART->EVENTS_TXDRDY = 0x0;
  Peripheral::UART->TXD = byte;
  while (!Peripheral::UART->EVENTS_TXDRDY && !Peripheral::UART->ERRORSRC)
    ;
  Peripheral::UART->ERRORSRC = 0x0;
};
char read(u32 timeout) {
  char inp = '\0';
  if (timeout == 0) {
    while (!Peripheral::UART->EVENTS_RXDRDY && !Peripheral::UART->ERRORSRC)
      ;
    Peripheral::UART->ERRORSRC = 0x0;
    inp = Peripheral::UART->RXD;
    Peripheral::UART->EVENTS_RXDRDY = 0x0;
  } else {
    Peripheral::TIMER1->PRESCALER = 0x4;
    Peripheral::TIMER1->EVENTS_COMPARE[0] = 0x0;
    Peripheral::TIMER1->CC[0] = timeout;
    Peripheral::TIMER1->BITMODE = 0x3;
    Peripheral::TIMER1->TASKS_CLEAR = 0x1;
    Peripheral::TIMER1->TASKS_START = 0x1;
    while (!Peripheral::UART->EVENTS_RXDRDY &&
           !Peripheral::TIMER1->EVENTS_COMPARE[0] &&
           !Peripheral::UART->ERRORSRC)
      ;
    if (Peripheral::TIMER1->EVENTS_COMPARE[0]) {
      inp = 0;
    }
    Peripheral::UART->ERRORSRC = 0x0;
    if (!Peripheral::TIMER1->EVENTS_COMPARE[0]) {
      inp = Peripheral::UART->RXD;
    }
    Peripheral::UART->EVENTS_RXDRDY = 0x0;
    Peripheral::TIMER1->TASKS_STOP = 0x1;
  }
  return inp;
}
} // namespace uart

namespace uarte { // TODO: prepsat input na uarte
void setBaudrate(BaudRate baudrate) {
  Peripheral::UARTE1->BAUDRATE = baudrate;
}
void startTX() {
  Peripheral::UARTE1->ENABLE = 0x8;
  // Peripheral::UARTE1->BAUDRATE = 0x01D7E000; // 115200 baud
  Peripheral::UARTE1->PSEL.TXD = Pin::UART_TX;
}
void stopTX() {
  Peripheral::UARTE1->PSEL.TXD = 0xFFFFFFFF;
  Peripheral::UARTE1->ENABLE = 0x0;
}
void startRX() {
  Peripheral::UARTE1->ENABLE = 0x8;
  // Peripheral::UARTE1->BAUDRATE = 0x01D7E000; // 115200 baud
  Peripheral::UARTE1->PSEL.RXD = Pin::UART_RX;
}
void stopRX() {
  Peripheral::UARTE1->PSEL.RXD = 0xFFFFFFFF;
  Peripheral::UARTE1->ENABLE = 0x0;
}
void write(const char* data, u16 size) {
  if (size == 0) {
    size = strlen(data);
  }
  char buf[size]; // TODO: vyresit: new/malloc/static/char[]
  memcpy(buf, data, size);
  Peripheral::UARTE1->TXD.MAXCNT = size;
  Peripheral::UARTE1->TXD.PTR = (ptr)buf;
  Peripheral::UARTE1->EVENTS_ENDTX = 0x0;
  Peripheral::UARTE1->EVENTS_TXSTARTED = 0x0;
  Peripheral::UARTE1->TASKS_STARTTX = 0x1;
  while (!Peripheral::UARTE1->EVENTS_TXSTARTED)
    ;
  while (!Peripheral::UARTE1->EVENTS_ENDTX && !Peripheral::UARTE1->ERRORSRC)
    ;
  Peripheral::UARTE1->ERRORSRC = 0x0;
  Peripheral::UARTE1->EVENTS_TXSTOPPED = 0x0;
  Peripheral::UARTE1->TASKS_STOPTX = 0x1;
  while (!Peripheral::UARTE1->EVENTS_TXSTOPPED)
    ;
};
char* read(u16 size, u32 timeout) {
  char* buf = (char*)malloc(size); // TODO: vyresit: new/malloc/static/char[]
  Peripheral::UARTE1->RXD.MAXCNT = size;
  Peripheral::UARTE1->RXD.PTR = (ptr)buf;
  Peripheral::UARTE1->EVENTS_ENDRX = 0x0;
  Peripheral::UARTE1->EVENTS_RXSTARTED = 0x0;
  Peripheral::UARTE1->TASKS_STARTRX = 0x1;
  while (!Peripheral::UARTE1->EVENTS_RXSTARTED)
    ;
  if (timeout != 0) {
    Peripheral::TIMER1->PRESCALER = 0x4;
    Peripheral::TIMER1->EVENTS_COMPARE[0] = 0x0;
    Peripheral::TIMER1->CC[0] = timeout;
    Peripheral::TIMER1->BITMODE = 0x3;
    Peripheral::TIMER1->TASKS_CLEAR = 0x1;
    Peripheral::TIMER1->TASKS_START = 0x1;
    while (!Peripheral::UARTE1->EVENTS_ENDRX && !Peripheral::UARTE1->ERRORSRC &&
           !Peripheral::TIMER1->EVENTS_COMPARE[0])
      ;
    if (Peripheral::TIMER1->EVENTS_COMPARE[0]) {
      free(buf); // TODO kdyz nebude malloc, tak ani free
      buf = nullptr;
    }
    Peripheral::TIMER1->TASKS_STOP = 0x1;
  } else {
    while (!Peripheral::UARTE1->EVENTS_ENDRX && !Peripheral::UARTE1->ERRORSRC)
      ;
  }
  Peripheral::UARTE1->ERRORSRC = 0x0;
  Peripheral::UARTE1->TASKS_STOPRX = 0x1;
  return buf; // TODO: uvolnit pamet
}
} // namespace uarte

///////////////////////////////////////////////////////////////////////////////

namespace pins {
void setMode(u8 pin, u32 mode) {
  if (pin < 32) {
    Peripheral::P0->PIN_CNF[pin] = mode;
  } else {
    Peripheral::P1->PIN_CNF[pin - 32] = mode;
  }
};
void setDigital(u8 pin, bool value) {
  u8 p = 0;
  if (pin >= 32) {
    pin -= 32;
    p = 1;
  }
  Peripheral::P[p]->PIN_CNF[pin] |= 0x1;
  value ? Peripheral::P[p]->OUTSET = 1 << pin
        : Peripheral::P[p]->OUTCLR = 1 << pin;
};
i8 getDigital(u8 pin, i8 none) {
  u8 p = 0;
  if (pin >= 32) {
    pin -= 32;
    p = 1;
  }
  Peripheral::P[p]->PIN_CNF[pin] &= ~0x0000000F;
  Peripheral::P[p]->PIN_CNF[pin] |= 0b0100;
  bool down = (Peripheral::P[p]->IN >> pin) & 0x1;
  Peripheral::P[p]->PIN_CNF[pin] |= 0b1100;
  bool up = (Peripheral::P[p]->IN >> pin) & 0x1;
  if (up && down) {
    return 1;
  }
  if (!up && !down) {
    return 0;
  }
  return none;
};
void setAnalog(u8 pin, u16 value, u32 period) {
  u32 ticks = (u32)(16 * period);
  u8 prescaler = 0;
  while ((ticks >> prescaler) > 32767 && prescaler < 7)
    prescaler++;
  u16 countertop = (ticks >> prescaler) - 1;
  if (value > 1023)
    value = 1023;
  volatile u16 seq = ((value * countertop) / 1023) | 1 << 15;
  u8 i = 0;
  for (; i < 4; i++) {
    if (Peripheral::PWM[i]->EVENTS_STOPPED ||
        Peripheral::PWM[i]->ENABLE == 0x0 ||
        Peripheral::PWM[i]->PSEL.OUT[0] == pin) {
      break;
    }
  }
  Peripheral::PWM[i]->ENABLE = 0x1;
  Peripheral::PWM[i]->EVENTS_STOPPED = 0x0;
  // EVENTS_SEQEND0 -> TASKS_STOP
  Peripheral::PWM[i]->SHORTS = 0x1;
  Peripheral::PWM[i]->COUNTERTOP = countertop;
  Peripheral::PWM[i]->PRESCALER = prescaler;
  Peripheral::PWM[i]->LOOP = 0x0;
  Peripheral::PWM[i]->SEQ[0].PTR = (ptr)&seq;
  Peripheral::PWM[i]->SEQ[0].CNT = 0x1;
  Peripheral::PWM[i]->PSEL.OUT[0] = pin;
  Peripheral::PWM[i]->EVENTS_SEQEND[0] = 0x0;
  Peripheral::PWM[i]->TASKS_SEQSTART[0] = 0x1;
}
u16 getAnalog(u8 pin) {
  u8 p = 0;
  volatile i16 value = 0;
  switch (pin) {
  case Pin::PIN_0:
    p = 1;
    break;
  case Pin::PIN_1:
    p = 2;
    break;
  case Pin::PIN_2:
    p = 3;
    break;
  case Pin::MIC_IN:
    p = 4;
    break;
  case Pin::PIN_4:
    p = 5;
    break;
  case 29:
    p = 6;
    break;
  case Pin::PIN_10:
    p = 7;
    break;
  case Pin::PIN_3:
    p = 8;
    break;
  default:
    return 0;
  }
  if (!Peripheral::SAADC->ENABLE ||
      Peripheral::SAADC->CH[0].CONFIG != 0x01001200) {
    Peripheral::SAADC->ENABLE = 0x1;
    Peripheral::SAADC->RESOLUTION = 0x1;
    // Bypass, Bypass, Gain 1/4, VDD 1/4, 3us, SE, Burst Enabled
    Peripheral::SAADC->CH[0].CONFIG = 0x01001200;
    Peripheral::SAADC->OVERSAMPLE = 0x8;
    Peripheral::SAADC->CH[0].PSELN = 0x0;
    Peripheral::SAADC->EVENTS_CALIBRATEDONE = 0x0;
    Peripheral::SAADC->TASKS_CALIBRATEOFFSET = 0x1;
    while (!Peripheral::SAADC->EVENTS_CALIBRATEDONE)
      ;
  }
  Peripheral::SAADC->CH[0].PSELP = p;
  Peripheral::SAADC->RESULT.PTR = (ptr)&value;
  Peripheral::SAADC->RESULT.MAXCNT = 0x1;
  Peripheral::SAADC->EVENTS_STARTED = 0x0;
  Peripheral::SAADC->TASKS_START = 0x1;
  while (!Peripheral::SAADC->EVENTS_STARTED)
    ;
  Peripheral::SAADC->EVENTS_END = 0x0;
  Peripheral::SAADC->TASKS_SAMPLE = 0x1;
  while (!Peripheral::SAADC->EVENTS_END)
    ;
  Peripheral::SAADC->EVENTS_STOPPED = 0x0;
  Peripheral::SAADC->TASKS_STOP = 0x1;
  while (!Peripheral::SAADC->EVENTS_STOPPED)
    ;
  if (value < 0)
    value = 0;
  return value;
}
} // namespace pins

///////////////////////////////////////////////////////////////////////////////

namespace i2c {
void init(u8 scl, u8 sda) {
  Peripheral::TWIM0->ENABLE = 0x6;
  Peripheral::TWIM0->PSEL.SCL = scl;
  Peripheral::TWIM0->PSEL.SDA = sda;
  Peripheral::TWIM0->FREQUENCY = 0x01980000; // 100 Kbps
  // Input, Connect, Pullup, S0D1, Sense Disabled
  pins::setMode(scl, 0x0000060C);
  pins::setMode(sda, 0x0000060C);
}
void writeBuffer(u8 address, const u8* data, u16 size) {
  u8 buf[size]; // TODO: vyresit: new/malloc/static/char[]
  memcpy(buf, data, size);
  Peripheral::TWIM0->TXD.PTR = (ptr)buf;
  Peripheral::TWIM0->TXD.MAXCNT = size;
  Peripheral::TWIM0->ADDRESS = address;
  Peripheral::TWIM0->EVENTS_LASTTX = 0x0;
  Peripheral::TWIM0->EVENTS_TXSTARTED = 0x0;
  Peripheral::TWIM0->TASKS_STARTTX = 0x1;
  while (!Peripheral::TWIM0->EVENTS_TXSTARTED)
    ;
  while (!Peripheral::TWIM0->EVENTS_LASTTX && !Peripheral::TWIM0->ERRORSRC)
    ;
  Peripheral::TWIM0->ERRORSRC = 0x0;
  Peripheral::TWIM0->EVENTS_STOPPED = 0x0;
  Peripheral::TWIM0->TASKS_STOP = 0x1;
  while (!Peripheral::TWIM0->EVENTS_STOPPED)
    ;
}
void writeByte(u8 address, u8 byte) {
  volatile u8 val = byte;
  Peripheral::TWIM0->TXD.PTR = (ptr)&val;
  Peripheral::TWIM0->TXD.MAXCNT = 0x1;
  Peripheral::TWIM0->ADDRESS = address;
  Peripheral::TWIM0->EVENTS_LASTTX = 0x0;
  Peripheral::TWIM0->EVENTS_TXSTARTED = 0x0;
  Peripheral::TWIM0->TASKS_STARTTX = 0x1;
  while (!Peripheral::TWIM0->EVENTS_TXSTARTED)
    ;
  while (!Peripheral::TWIM0->EVENTS_LASTTX && !Peripheral::TWIM0->ERRORSRC)
    ;
  Peripheral::TWIM0->ERRORSRC = 0x0;
  Peripheral::TWIM0->EVENTS_STOPPED = 0x0;
  Peripheral::TWIM0->TASKS_STOP = 0x1;
  while (!Peripheral::TWIM0->EVENTS_STOPPED)
    ;
}
u8* readBuffer(u8 address, u16 size) {
  u8* buf = (u8*)malloc(size); // TODO: vyresit: new/malloc/static/char[]
  Peripheral::TWIM0->RXD.PTR = (ptr)buf;
  Peripheral::TWIM0->RXD.MAXCNT = size;
  Peripheral::TWIM0->ADDRESS = address;
  Peripheral::TWIM0->EVENTS_RXSTARTED = 0x0;
  Peripheral::TWIM0->EVENTS_LASTRX = 0x0;
  Peripheral::TWIM0->TASKS_STARTRX = 0x1;
  while (!Peripheral::TWIM0->EVENTS_RXSTARTED)
    ;
  while (!Peripheral::TWIM0->EVENTS_LASTRX && !Peripheral::TWIM0->ERRORSRC)
    ;
  Peripheral::TWIM0->ERRORSRC = 0x0;
  Peripheral::TWIM0->EVENTS_STOPPED = 0x0;
  Peripheral::TWIM0->TASKS_STOP = 0x1;
  while (!Peripheral::TWIM0->EVENTS_STOPPED)
    ;
  return buf; // TODO: uvolnit pamet
}
u8 readByte(u8 address) {
  volatile u8 val = 0;
  Peripheral::TWIM0->RXD.PTR = (ptr)&val;
  Peripheral::TWIM0->RXD.MAXCNT = 0x1;
  Peripheral::TWIM0->ADDRESS = address;
  Peripheral::TWIM0->EVENTS_RXSTARTED = 0x0;
  Peripheral::TWIM0->EVENTS_LASTRX = 0x0;
  Peripheral::TWIM0->TASKS_STARTRX = 0x1;
  while (!Peripheral::TWIM0->EVENTS_RXSTARTED)
    ;
  while (!Peripheral::TWIM0->EVENTS_LASTRX && !Peripheral::TWIM0->ERRORSRC)
    ;
  Peripheral::TWIM0->ERRORSRC = 0x0;
  Peripheral::TWIM0->EVENTS_STOPPED = 0x0;
  Peripheral::TWIM0->TASKS_STOP = 0x1;
  while (!Peripheral::TWIM0->EVENTS_STOPPED)
    ;
  return val;
}
} // namespace i2c

///////////////////////////////////////////////////////////////////////////////

namespace radio {
void init() {
  Peripheral::RADIO->TXPOWER = 0x0;
  Peripheral::RADIO->FREQUENCY = 0x7;
  Peripheral::RADIO->MODE = 0x0;
  Peripheral::RADIO->BASE0 = 0x75626974;
  Peripheral::RADIO->PREFIX0 = 0x0;
  Peripheral::RADIO->TXADDRESS = 0x0;
  Peripheral::RADIO->RXADDRESSES = 0x1;
  // 8bit LENGTH field, no S0/S1, 8bit preamble, exclude CRC from LENGTH
  Peripheral::RADIO->PCNF0 = 0x00000008;
  // 32B payload, 4B base addr, little-endian, whitening on
  Peripheral::RADIO->PCNF1 = 0x02040020;
  Peripheral::RADIO->CRCCNF = 0x2;
  Peripheral::RADIO->CRCPOLY = 0x11021;
  Peripheral::RADIO->CRCINIT = 0xFFFF;
  Peripheral::RADIO->DATAWHITEIV = 0x18;
  Peripheral::RADIO->SHORTS = 0x10;
}
void send(u8* packet) {
  Peripheral::RADIO->PACKETPTR = (ptr)packet;
  Peripheral::RADIO->EVENTS_READY = 0x0;
  Peripheral::RADIO->TASKS_TXEN = 0x1;
  while (!Peripheral::RADIO->EVENTS_READY)
    ;
  Peripheral::RADIO->EVENTS_END = 0x0;
  Peripheral::RADIO->TASKS_START = 0x1;
  while (!Peripheral::RADIO->EVENTS_END)
    ;
  Peripheral::RADIO->EVENTS_DISABLED = 0x0;
  Peripheral::RADIO->TASKS_DISABLE = 0x1;
  while (!Peripheral::RADIO->EVENTS_DISABLED)
    ;
}
u8* recieve(u32 timeout) {
  u8* buf = (u8*)malloc(32); // TODO: free
  Peripheral::RADIO->PACKETPTR = (ptr)buf;
  Peripheral::RADIO->EVENTS_READY = 0x0;
  Peripheral::RADIO->TASKS_RXEN = 0x1;
  while (!Peripheral::RADIO->EVENTS_READY)
    ;
  Peripheral::RADIO->EVENTS_END = 0x0;
  Peripheral::RADIO->EVENTS_ADDRESS = 0x0;
  Peripheral::RADIO->TASKS_START = 0x1;
  if (timeout != 0) {
    Peripheral::TIMER1->PRESCALER = 0x4;
    Peripheral::TIMER1->EVENTS_COMPARE[0] = 0x0;
    Peripheral::TIMER1->CC[0] = timeout;
    Peripheral::TIMER1->BITMODE = 0x3;
    Peripheral::TIMER1->TASKS_CLEAR = 0x1;
    Peripheral::TIMER1->TASKS_START = 0x1;
    while (!Peripheral::RADIO->EVENTS_ADDRESS &&
           !Peripheral::TIMER1->EVENTS_COMPARE[0])
      ;
    if (Peripheral::TIMER1->EVENTS_COMPARE[0]) {
      free(buf);
      buf = nullptr;
    }
    Peripheral::TIMER1->TASKS_STOP = 0x1;
    while (!Peripheral::RADIO->EVENTS_END &&
           !Peripheral::TIMER1->EVENTS_COMPARE[0])
      ;
  } else {
    while (!Peripheral::RADIO->EVENTS_END)
      ;
  }
  if (!Peripheral::RADIO->CRCSTATUS) {
    buf = nullptr;
  }
  Peripheral::RADIO->EVENTS_DISABLED = 0x0;
  Peripheral::RADIO->TASKS_DISABLE = 0x1;
  while (!Peripheral::RADIO->EVENTS_DISABLED)
    ;
  return buf;
}
u8 getSignalStrength() {
  return Peripheral::RADIO->RSSISAMPLE;
}
void setChannel(u32 channel) {
  if ((channel < 0) || (channel > 83))
    return;
  Peripheral::RADIO->FREQUENCY = channel;
}
void setGroup(u32 group) {
  if ((group < 0) || (group > 255))
    return;
  Peripheral::RADIO->PREFIX0 = group;
}
} // namespace radio

///////////////////////////////////////////////////////////////////////////////

namespace sensors {
i16 microphone() {
  volatile i16 value = 0;
  if (!Peripheral::SAADC->ENABLE ||
      Peripheral::SAADC->CH[0].CONFIG != 0x01000700) {
    Peripheral::SAADC->ENABLE = 0x1;
    Peripheral::SAADC->RESOLUTION = 0x1;
    // Bypass, Bypass, Gain 4, Internal, 3us, SE, Burst Enabled
    Peripheral::SAADC->CH[0].CONFIG = 0x01000700;
    Peripheral::SAADC->OVERSAMPLE = 0x8;
    Peripheral::SAADC->CH[0].PSELN = 0x0;
    Peripheral::SAADC->EVENTS_CALIBRATEDONE = 0x0;
    Peripheral::SAADC->TASKS_CALIBRATEOFFSET = 0x1;
    while (!Peripheral::SAADC->EVENTS_CALIBRATEDONE)
      ;
  }
  Peripheral::SAADC->CH[0].PSELP = 0x4;
  Peripheral::SAADC->RESULT.PTR = (ptr)&value;
  Peripheral::SAADC->RESULT.MAXCNT = 0x1;
  Peripheral::SAADC->EVENTS_STARTED = 0x0;
  Peripheral::SAADC->TASKS_START = 0x1;
  while (!Peripheral::SAADC->EVENTS_STARTED)
    ;
  Peripheral::SAADC->EVENTS_END = 0x0;
  Peripheral::SAADC->TASKS_SAMPLE = 0x1;
  while (!Peripheral::SAADC->EVENTS_END)
    ;
  Peripheral::SAADC->EVENTS_STOPPED = 0x0;
  Peripheral::SAADC->TASKS_STOP = 0x1;
  while (!Peripheral::SAADC->EVENTS_STOPPED)
    ;
  if (value < 0)
    value = 0;
  return (value - 556) << 1;
}
float temperature() {
  Peripheral::TEMP->EVENTS_DATARDY = 0x0;
  Peripheral::TEMP->TASKS_START = 0x1;
  while (!Peripheral::TEMP->EVENTS_DATARDY)
    ;
  float temp = ((i64)(i32)Peripheral::TEMP->TEMP) * 0.25f;
  Peripheral::TEMP->TASKS_STOP = 0x1;
  return temp;
}
void writeReg(u8 reg, u8 val) {
  volatile u8 buf[2] = {reg, val};
  Peripheral::TWIM1->TXD.PTR = (ptr)buf;
  Peripheral::TWIM1->TXD.MAXCNT = 0x2;
  Peripheral::TWIM1->EVENTS_TXSTARTED = 0x0;
  Peripheral::TWIM1->EVENTS_LASTTX = 0x0;
  Peripheral::TWIM1->TASKS_STARTTX = 0x1;
  while (!Peripheral::TWIM1->EVENTS_TXSTARTED)
    ;
  while (!Peripheral::TWIM1->EVENTS_LASTTX && !Peripheral::TWIM1->ERRORSRC)
    ;
  Peripheral::TWIM1->ERRORSRC = 0x0;
  Peripheral::TWIM1->EVENTS_STOPPED = 0x0;
  Peripheral::TWIM1->TASKS_STOP = 0x1;
  while (!Peripheral::TWIM1->EVENTS_STOPPED)
    ;
}
u8 readReg(u8 reg) {
  volatile u8 buf = reg;
  volatile u8 val = 0;
  Peripheral::TWIM1->TXD.PTR = (ptr)&buf;
  Peripheral::TWIM1->TXD.MAXCNT = 0x1;
  Peripheral::TWIM1->RXD.PTR = (ptr)&val;
  Peripheral::TWIM1->RXD.MAXCNT = 0x1;
  Peripheral::TWIM1->EVENTS_TXSTARTED = 0x0;
  Peripheral::TWIM1->EVENTS_RXSTARTED = 0x0;
  Peripheral::TWIM1->EVENTS_LASTTX = 0x0;
  Peripheral::TWIM1->EVENTS_LASTRX = 0x0;
  Peripheral::TWIM1->TASKS_STARTTX = 0x1;
  while (!Peripheral::TWIM1->EVENTS_TXSTARTED)
    ;
  while (!Peripheral::TWIM1->EVENTS_LASTTX && !Peripheral::TWIM1->ERRORSRC)
    ;
  Peripheral::TWIM1->ERRORSRC = 0x0;
  Peripheral::TWIM1->TASKS_STARTRX = 0x1;
  while (!Peripheral::TWIM1->EVENTS_RXSTARTED)
    ;
  while (!Peripheral::TWIM1->EVENTS_LASTRX && !Peripheral::TWIM1->ERRORSRC)
    ;
  Peripheral::TWIM1->ERRORSRC = 0x0;
  Peripheral::TWIM1->EVENTS_STOPPED = 0x0;
  Peripheral::TWIM1->TASKS_STOP = 0x1;
  while (!Peripheral::TWIM1->EVENTS_STOPPED)
    ;
  return val;
}
vec accelerometer() {
  if (Peripheral::TWIM1->ENABLE != 0x6) {
    Peripheral::TWIM1->ENABLE = 0x6;
    Peripheral::TWIM1->PSEL.SCL = Pin::I2C_INT_SCL;
    Peripheral::TWIM1->PSEL.SDA = Pin::I2C_INT_SDA;
    Peripheral::TWIM1->FREQUENCY = 0x01980000; // 100 Kbps
    // Input, Connect, Pullup, S0D1, Sense Disabled
    pins::setMode(Pin::I2C_INT_SCL, 0x0000060C);
    pins::setMode(Pin::I2C_INT_SDA, 0x0000060C);
  }
  Peripheral::TWIM1->ADDRESS = 0x19;
  writeReg(0x20, 0x57);
  writeReg(0x23, 0x88);
  vec val;
  val.x = (i16)((readReg(0x29) << 8) | readReg(0x28));
  val.y = (i16)((readReg(0x2B) << 8) | readReg(0x2A));
  val.z = (i16)((readReg(0x2D) << 8) | readReg(0x2C));
  return val;
}
vec magnetometer() {
  if (Peripheral::TWIM1->ENABLE != 0x6) {
    Peripheral::TWIM1->ENABLE = 0x6;
    Peripheral::TWIM1->PSEL.SCL = Pin::I2C_INT_SCL;
    Peripheral::TWIM1->PSEL.SDA = Pin::I2C_INT_SDA;
    Peripheral::TWIM1->FREQUENCY = 0x01980000; // 100 Kbps
    // Input, Connect, Pullup, S0D1, Sense Disabled
    pins::setMode(Pin::I2C_INT_SCL, 0x0000060C);
    pins::setMode(Pin::I2C_INT_SDA, 0x0000060C);
  }
  Peripheral::TWIM1->ADDRESS = 0x1E;
  writeReg(0x60, 0x80);
  writeReg(0x62, 0x10);
  vec val;
  val.x = (i16)((readReg(0x69) << 8) | readReg(0x68));
  val.y = (i16)((readReg(0x6B) << 8) | readReg(0x6A));
  val.z = (i16)((readReg(0x6D) << 8) | readReg(0x6C));
  return val;
}
// TODO
/*
vec scale = {1, 1, 1};
u32 compass() {
  vec acc = accelerometer();
  vec mag = magnetometer() * scale;
  double roll = atan2(acc.y, acc.z);
  double pitch = atan2(-acc.x, sqrt(acc.y * acc.y + acc.z * acc.z));
  double mx = mag.x * cos(pitch) + mag.z * sin(pitch);
  double my = mag.x * sin(roll) * sin(pitch) + mag.y * cos(roll) -
              mag.z * sin(roll) * cos(pitch);
  double heading = atan2(-my, mx);
  if (heading < 0)
    heading += 2 * M_PI;
  heading = heading * 180.0 / M_PI;
  return heading;
}
void calibrateCompass() {
  u32 i = 2000;
  vec min = {0, 0, 0};
  vec max = {0, 0, 0};
  while (i--) {
    print((string)i);
    vec mag = magnetometer();
    if (mag.x < min.x)
      min.x = mag.x;
    if (mag.y < min.y)
      min.y = mag.y;
    if (mag.z < min.z)
      min.z = mag.z;
    if (mag.x > max.x)
      max.x = mag.x;
    if (mag.y > max.y)
      max.y = mag.y;
    if (mag.z > max.z)
      max.z = mag.z;
  }
  vec offset = {
      (max.x + min.x) / 2,
      (max.y + min.y) / 2,
      (max.z + min.z) / 2,
  };
  float rx = (max.x - min.x) / 2.0;
  float ry = (max.y - min.y) / 2.0;
  float rz = (max.z - min.z) / 2.0;
  float rmean = (rx + ry + rz) / 3.0f;
  scale = {(i32)(rmean / rx), (i32)(rmean / ry), (i32)(rmean / rz)};
  writeReg(0x45, offset.x & 0xFF);
  writeReg(0x46, offset.x >> 8);
  writeReg(0x47, offset.y & 0xFF);
  writeReg(0x48, offset.y >> 8);
  writeReg(0x49, offset.z & 0xFF);
  writeReg(0x4A, offset.z >> 8);
}
*/
} // namespace sensors

///////////////////////////////////////////////////////////////////////////////

namespace sound {
void tone(float freq, u64 duration, u8 volume) {
  // TODO
  u32 period_us = 1000000 / freq;
  u32 high_time = (period_us * volume) / 100;
  u32 low_time = period_us - high_time;
  while (duration--) {
    pins::setDigital(Pin::SPEAKER, 1);
    volatile u32 x = high_time * 6;
    while (x--)
      ;
    pins::setDigital(Pin::SPEAKER, 0);
    volatile u32 y = low_time * 6;
    while (y--)
      ;
  }
}
} // namespace sound

///////////////////////////////////////////////////////////////////////////////

void wait(u64 us) {
  Peripheral::TIMER0->BITMODE = 0x3;
  Peripheral::TIMER0->CC[0] = us;
  Peripheral::TIMER0->EVENTS_COMPARE[0] = 0x0;
  Peripheral::TIMER0->TASKS_CLEAR = 0x1;
  Peripheral::TIMER0->TASKS_START = 0x1;
  while (!Peripheral::TIMER0->EVENTS_COMPARE[0])
    ;
  Peripheral::TIMER0->TASKS_STOP = 0x1;
}
u32 millis() {
  return Peripheral::RTC2->COUNTER * 125; // TODO: nepresne
}
u32 micros() {
  Peripheral::TIMER2->TASKS_CAPTURE[0] = 0x1;
  return Peripheral::TIMER2->CC[0];
}

u8 rnd() {
  Peripheral::RNG->TASKS_START = 0x1;
  while (!Peripheral::RNG->EVENTS_VALRDY)
    ;
  return Peripheral::RNG->VALUE;
}
void print(const char* text, const char* end) {
  uarte::startTX();
  uarte::write(text);
  uarte::write(end);
  uarte::stopTX();
}
string input(const char* text, const char* end) {
  print(text, "");
  u32 size = 1;
  uart::startRX();
  string buf = "";
  int pos = 0;
  while (1) {
    char inp = uart::read();
    for (u32 i = 0; end[i] != '\0'; i++) {
      if (inp == end[i]) {
        uart::stopRX();
        print("");
        return buf;
      }
    }
    if ((inp == 0x08 || inp == 0x7F) && pos > 0) {
      buf.pop_back();
      print("\b \b", "");
      continue;
    }
    if (inp < 32) {
      continue;
    }
    buf.push_back(inp);
    char str[2] = {inp, '\0'};
    print(str, "");
  }
}
} // namespace microbit
