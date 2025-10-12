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
#include <cstdlib>
#include <cstring>

typedef signed char i8;
typedef unsigned char u8;
typedef signed short i16;
typedef unsigned short u16;
typedef signed int i32;
typedef unsigned int u32;
typedef signed long long int i64;
typedef unsigned long long int u64;

typedef volatile unsigned long int ptr;

static void msga(const char* str) { // TODO: remove (debug)
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

template <u32 SIZE>
class Heap {
private:
  constexpr static u32 BLOCKS = SIZE / 8;
  struct {
    u16 pointer;
    u16 len;
  } list[BLOCKS];
  u8 pool[SIZE];

public:
  Heap() {
    for (u32 i = 0; i < BLOCKS; i++) {
      list[i].pointer = 0;
      list[i].len = 0;
    }
  }
  void free(void* pointer) {
    for (u32 i = 0; i < BLOCKS; i++) {
      if (list[i].pointer == (u16)((u8*)pointer - pool)) {
        list[i].pointer = 0;
        list[i].len = 0;
        break;
      }
    }
  }
  void* alloc(u32 size) {
    u32 pointer = 0;
  loop:
    for (u32 i = 0; i < BLOCKS; i++) {
      if (pointer + size <= list[i].pointer)
        continue;
      if (pointer >= list[i].pointer + list[i].len)
        continue;
      pointer = list[i].pointer + list[i].len;
      if (pointer + size > SIZE)
        return nullptr;
      goto loop;
    }
    for (u32 i = 0; i < BLOCKS; i++) {
      if (list[i].len == 0) {
        list[i].pointer = pointer;
        list[i].len = size;
        break;
      }
    }
    return (void*)(pool + pointer);
  }
  void* calloc(u32 size, u8 type_size) {
    void* p = alloc(size * type_size);
    if (p == nullptr)
      return nullptr;
    memset(p, 0, size * type_size);
    return p;
  }
};

class string {
private:
  char* data = nullptr;
  u32 len = 0; // without terminating null character
  u32 cap = 16;

public:
  ~string() {
    free(data);
  }
  string(const string& other) {
    len = other.len;
    while (cap <= len)
      cap *= 2;
    data = (char*)calloc(cap, sizeof(char));
    if (data == nullptr)
      return;
    memcpy(data, other.data, len + 1);
  }
  string() {
    data = (char*)calloc(cap, sizeof(char));
    if (data == nullptr)
      return;
  }
  string(const char* c) {
    if (c == nullptr) {
      data = (char*)calloc(cap, sizeof(char));
      return;
    }
    len = strlen(c);
    while (cap <= len)
      cap *= 2;
    data = (char*)calloc(cap, sizeof(char));
    if (data == nullptr)
      return;
    memcpy(data, c, len + 1);
  }
  string(i8 c, u32 radix = 10) : string((i32)c, radix) {};
  string(i16 c, u32 radix = 10) : string((i32)c, radix) {};
  string(u8 c, u32 radix = 10) : string((u32)c, radix) {};
  string(u16 c, u32 radix = 10) : string((u32)c, radix) {};
  string(ptr c, u32 radix = 10) : string((u32)c, radix) {};
  string(i32 c, u32 radix = 10) {
    if (radix > 36 || radix < 2) {
      len = 0;
      data = (char*)calloc(cap, sizeof(char));
      if (data == nullptr)
        return;
      data[0] = '\0';
      return;
    }
    char buffer[32];
    int i = 0;
    bool negative = false;
    if (c == 0) {
      len = 1;
      data = (char*)calloc(cap, sizeof(char));
      if (data == nullptr)
        return;
      data[0] = '0';
      return;
    }
    if (c < 0) {
      negative = true;
    }
    u64 n = negative ? (u64)(-(c + 1)) + 1 : (u64)c;
    while (n != 0) {
      u32 digit = (n % radix);
      buffer[i++] = digit < 10 ? '0' + digit : 'a' + digit - 10;
      n /= radix;
    }
    if (negative) {
      buffer[i++] = '-';
    }
    len = i;
    while (cap <= len)
      cap *= 2;
    data = (char*)calloc(cap, sizeof(char));
    if (data == nullptr)
      return;
    int j = 0;
    while (i > 0) {
      data[j++] = buffer[--i];
    }
    data[len] = '\0';
  };
  string(u32 c, u32 radix = 10) {
    if (radix > 36 || radix < 2) {
      len = 0;
      data = (char*)calloc(cap, sizeof(char));
      if (data == nullptr)
        return;
      data[0] = '\0';
      return;
    }
    char buffer[32];
    int i = 0;
    if (c == 0) {
      len = 1;
      data = (char*)calloc(cap, sizeof(char));
      if (data == nullptr)
        return;
      data[0] = '0';
      return;
    }
    u64 n = c;
    while (n != 0) {
      u32 digit = (n % radix);
      buffer[i++] = digit < 10 ? '0' + digit : 'a' + digit - 10;
      n /= radix;
    }
    len = i;
    while (cap <= len)
      cap *= 2;
    data = (char*)calloc(cap, sizeof(char));
    if (data == nullptr)
      return;
    int j = 0;
    while (i > 0) {
      data[j++] = buffer[--i];
    }
    data[len] = '\0';
  };
  string(i64 c, u32 radix = 10) {
    if (radix > 36 || radix < 2) {
      len = 0;
      data = (char*)calloc(cap, sizeof(char));
      if (data == nullptr)
        return;
      data[0] = '\0';
      return;
    }
    char buffer[32];
    int i = 0;
    bool negative = false;
    if (c == 0) {
      len = 1;
      data = (char*)calloc(cap, sizeof(char));
      if (data == nullptr)
        return;
      data[0] = '0';
      return;
    }
    if (c < 0) {
      negative = true;
    }
    u64 n = negative ? (u64)(-(c + 1)) + 1 : (u64)c;
    while (n != 0) {
      u32 digit = (n % radix);
      buffer[i++] = digit < 10 ? '0' + digit : 'a' + digit - 10;
      n /= radix;
    }
    if (negative) {
      buffer[i++] = '-';
    }
    len = i;
    while (cap <= len)
      cap *= 2;
    data = (char*)calloc(cap, sizeof(char));
    if (data == nullptr)
      return;
    int j = 0;
    while (i > 0) {
      data[j++] = buffer[--i];
    }
    data[len] = '\0';
  }
  string(u64 c, u32 radix = 10) {
    if (radix > 36 || radix < 2) {
      len = 0;
      data = (char*)calloc(cap, sizeof(char));
      if (data == nullptr)
        return;
      data[0] = '\0';
      return;
    }
    char buffer[32];
    int i = 0;
    if (c == 0) {
      len = 1;
      data = (char*)calloc(cap, sizeof(char));
      if (data == nullptr)
        return;
      data[0] = '0';
      return;
    }
    u64 n = c;
    while (n != 0) {
      u32 digit = (n % radix);
      buffer[i++] = digit < 10 ? '0' + digit : 'a' + digit - 10;
      n /= radix;
    }
    len = i;
    while (cap <= len)
      cap *= 2;
    data = (char*)calloc(cap, sizeof(char));
    if (data == nullptr)
      return;
    int j = 0;
    while (i > 0) {
      data[j++] = buffer[--i];
    }
    data[len] = '\0';
  }
  string(float c, u16 precision = 9) {
    u32 num = *(u32*)&c;
    bool sign = num >> 31;
    u8 exp = (num >> 23) & 0xFF;
    u32 frac = num & 0x7FFFFF;
    if (exp == 255) {
      if (frac == 0)
        *this = sign ? string("-inf") : string("inf");
      else
        *this = sign ? string("-NaN") : string("NaN");
      return;
    }
    if (exp == 0 && frac == 0) {
      *this = sign ? string("-0") : string("0");
      return;
    }
    u64 mant = frac | (exp != 0 ? (1ULL << 23) : 0);
    if (exp == 0)
      exp = 1;
    i32 e = (i32)exp - 127 - 23;
    u64 intpart = (e >= 0) ? (mant << e) : (mant >> -e);
    u64 rem = (e >= 0) ? 0 : mant - (intpart << -e);
    *this = string(sign ? "-" : "") + string(intpart);
    if (rem) {
      *this += '.';
      for (u16 i = 0; i < precision && rem; i++) {
        rem *= 10;
        u32 digit = rem >> (u32)-e;
        *this += ('0' + digit);
        rem &= ((1ULL << -e) - 1);
      }
    }
  }
  void push_back(const char c) {
    push(c, -1);
  }
  void push_front(const char c) {
    push(c, 0);
  }
  void push(const char c, const i32 index) {
    u32 i = index;
    if (index < 0) {
      i = len + index + 1;
      if (-index - 1 > len)
        i = 0;
    }
    if (i > len)
      i = len;
    while (cap <= len + 1)
      cap *= 2;
    data = (char*)realloc(data, cap * sizeof(char));
    if (data == nullptr)
      return;
    memmove(data + i + 1, data + i, len - i + 1);
    len++;
    data[i] = c;
  }
  char pop_back() {
    return pop(-1);
  }
  char pop_front() {
    return pop(0);
  }
  char pop(const i32 index) {
    u32 i = index;
    if (index < 0) {
      i = len + index;
      if (-index > len)
        i = 0;
    }
    if (i >= len)
      i = len - 1;
    char ret = data[i];
    memmove(data + i, data + i + 1, len - i);
    len--;
    data[len] = '\0';
    return ret;
  }
  char* c_str() {
    return data;
  }
  const char* c_str() const {
    return data;
  }
  operator char*() {
    return data;
  }
  operator const char*() const {
    return data;
  }
  char& operator[](i32 index) {
    u32 i = index;
    if (index < 0) {
      i = len + index;
      if (-index > len)
        i = 0;
    }
    if (i >= len)
      i = len - 1;
    return data[i];
  }
  const char operator[](i32 index) const {
    u32 i = index;
    if (index < 0) {
      i = len + index;
      if (-index > len)
        i = 0;
    }
    if (i >= len)
      i = len - 1;
    return data[i];
  }
  char* begin() {
    return data;
  }
  char* end() {
    return data + len;
  }
  const char* begin() const {
    return data;
  }
  const char* end() const {
    return data + len;
  }
  u32 size() {
    return len;
  }
  const u32 size() const {
    return len;
  }
  string operator+(const string& other) const {
    string n;
    n.len = len + other.len;
    while (n.cap <= n.len)
      n.cap *= 2;
    free(n.data);
    n.data = (char*)calloc(n.cap, sizeof(char));
    if (n.data == nullptr)
      return string();
    memcpy(n.data, data, len);
    memcpy(n.data + len, other.data, other.len + 1);
    return n;
  }
  template <typename T>
  string operator+(const char* other) const {
    string tmp = other;
    return *this + tmp;
  }
  string operator*(const u32 other) const {
    string n;
    n.len = len * other;
    while (n.cap <= n.len)
      n.cap *= 2;
    free(n.data);
    n.data = (char*)calloc(n.cap, sizeof(char));
    if (n.data == nullptr)
      return string();
    for (u32 i = 0; i < other; i++) {
      memcpy(n.data + i * len, data, len);
    }
    return n;
  }
  string& operator=(const string& other) {
    if (this == &other)
      return *this;
    free(data);
    len = other.len;
    while (cap <= len)
      cap *= 2;
    data = (char*)calloc(cap, sizeof(char));
    if (data)
      memcpy(data, other.data, len);
    return *this;
  }
  string& operator+=(const char other) {
    push_back(other);
    return *this;
  }
};
