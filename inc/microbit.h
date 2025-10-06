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
#include "peripheral.h"
#include "types.h"

namespace microbit {
namespace uart {
enum BaudRate {
  Baud1200 = 0x0004F000,
  Baud2400 = 0x0009D000,
  Baud4800 = 0x0013B000,
  Baud9600 = 0x00275000,
  Baud14400 = 0x003B0000,
  Baud19200 = 0x004EA000,
  Baud28800 = 0x0075F000,
  Baud31250 = 0x00800000,
  Baud38400 = 0x009D5000,
  Baud56000 = 0x00E50000,
  Baud57600 = 0x00EBF000,
  Baud76800 = 0x013A9000,
  Baud115200 = 0x01D7E000,
  Baud230400 = 0x03AFB000,
  Baud250000 = 0x04000000,
  Baud460800 = 0x075F7000,
  Baud921600 = 0x0EBED000,
  Baud1M = 0x10000000
};
void setBaudrate(BaudRate baudrate);
void startTX();
void stopTX();
void startRX();
void stopRX();
void write(char byte);
char read(u32 timeout = 0);
} // namespace uart

namespace uarte {
enum BaudRate {
  Baud1200 = 0x0004F000,
  Baud2400 = 0x0009D000,
  Baud4800 = 0x0013B000,
  Baud9600 = 0x00275000,
  Baud14400 = 0x003B0000,
  Baud19200 = 0x004EA000,
  Baud28800 = 0x0075F000,
  Baud31250 = 0x00800000,
  Baud38400 = 0x009D5000,
  Baud56000 = 0x00E50000,
  Baud57600 = 0x00EBF000,
  Baud76800 = 0x013A9000,
  Baud115200 = 0x01D7E000,
  Baud230400 = 0x03AFB000,
  Baud250000 = 0x04000000,
  Baud460800 = 0x075F7000,
  Baud921600 = 0x0EBED000,
  Baud1M = 0x10000000
};
void setBaudrate(BaudRate baudrate);
void startTX();
void stopTX();
void startRX();
void stopRX();
void write(const char* byte, u16 size = 0);
char* read(u16 size, u32 timeout = 0);
} // namespace uarte

namespace pins {
void setMode(u8 pin, u32 mode);
void setDigital(u8 pin, bool value);
i8 getDigital(u8 pin, i8 none = -1);
void setAnalog(u8 pin, u16 value, u32 period);

u16 getAnalog(u8 pin);
} // namespace pins

namespace i2c {
void init(u8 scl = Pin::I2C_SCL, u8 sda = Pin::I2C_SDA);
void writeBuffer(u8 address, const u8* data, u16 size);
void writeByte(u8 address, u8 byte);
u8* readBuffer(u8 address, u16 size);
u8 readByte(u8 address);
} // namespace i2c

namespace radio {
void init();
void send(u8* packet);
u8* recieve();
} // namespace radio

namespace sensors {
struct vec {
  i32 x;
  i32 y;
  i32 z;
};
i16 microphone();
float temperature();
vec accelerometer();
vec magnetometer();
/*
u32 compass();
void calibrateCompass();
*/
} // namespace sensors

namespace sound {
using sensors::microphone;
void tone(float freq, u64 duration, u8 volume = 100);
} // namespace sound

u8 rnd();
void print(const char* text, const char* end = "\n\r");
string input(const char* text, const char* end = "\n\r\4\3");
} // namespace microbit
