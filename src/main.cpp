#include "microbit.h"
#include "peripheral.h"

inline volatile void delay(volatile u32 cycles) {
  while (cycles--)
    ;
}
#define C2 65
#define C2s 69
#define D2b 69
#define D2 73
#define D2s 78
#define E2b 78
#define E2 82
#define F2 87
#define F2s 93
#define G2b 93
#define G2 98
#define G2s 104
#define A2b 104
#define A2 110
#define A2s 117
#define B2b 117
#define B2 123

#define C3 131
#define C3s 139
#define D3b 139
#define D3 147
#define D3s 156
#define E3b 156
#define E3 165
#define F3 175
#define F3s 185
#define G3b 185
#define G3 196
#define G3s 208
#define A3b 208
#define A3 220
#define A3s 233
#define B3b 233
#define B3 247

#define C4 262
#define C4s 277
#define D4b 277
#define D4 294
#define D4s 311
#define E4b 311
#define E4 330
#define F4 349
#define F4s 370
#define G4b 370
#define G4 392
#define G4s 415
#define A4b 415
#define A4 440
#define A4s 466
#define B4b 466
#define B4 494

#define C5 523
#define C5s 554
#define D5b 554
#define D5 587
#define D5s 622
#define E5b 622
#define E5 659
#define F5 698
#define F5s 740
#define G5b 740
#define G5 784
#define G5s 831
#define A5b 831
#define A5 880
#define A5s 932
#define B5b 932
#define B5 988

#define C6 1047
#define C6s 1109
#define D6b 1109
#define D6 1175
#define D6s 1245
#define E6b 1245
#define E6 1319
#define F6 1397
#define F6s 1480
#define G6b 1480
#define G6 1568
#define G6s 1661
#define A6b 1661
#define A6 1760
#define A6s 1865
#define B6b 1865
#define B6 1976

#define R 0

// static const double s[] = {C2, C2s, D2, D2s, E2, F2, F2s, G2, G2s, A2, A2s,
// B2,
//                            C3, C3s, D3, D3s, E3, F3, F3s, G3, G3s, A3, A3s,
//                            B3, C4, C4s, D4, D4s, E4, F4, F4s, G4, G4s, A4,
//                            A4s, B4, C5, C5s, D5, D5s, E5, F5, F5s, G5, G5s,
//                            A5, A5s, B5, C6, C6s, D6, D6s, E6, F6, F6s, G6,
//                            G6s, A6, A6s, B6};

u16 const x[] = {
    D4,  479, R, 1,   D4,  239, R, 1,   D4,  479, R, 1,   D4,  239, R, 1,
    D4,  479, R, 1,   D4,  239, R, 1,   D4,  239, R, 1,   D4,  239, R, 1,
    D4,  239, R, 1,   D4,  479, R, 1,   D4,  239, R, 1,   D4,  479, R, 1,
    D4,  239, R, 1,   D4,  479, R, 1,   D4,  239, R, 1,   D4,  239, R, 1,
    D4,  239, R, 1,   D4,  239, R, 1,   D4,  479, R, 1,   D4,  239, R, 1,
    D4,  479, R, 1,   D4,  239, R, 1,   D4,  479, R, 1,   D4,  239, R, 1,
    D4,  239, R, 1,   A3,  239, R, 1,   C4,  239, R, 1,   D4,  479, R, 1,
    D4,  359, R, 121, D4,  239, R, 1,   E4,  239, R, 1,   F4,  479, R, 1,
    F4,  359, R, 121, F4,  239, R, 1,   G4,  239, R, 1,   E4,  479, R, 1,
    E4,  359, R, 121, D4,  239, R, 1,   C4,  239, R, 1,   C4,  239, R, 1,
    D4,  479, R, 241, A3,  239, R, 1,   C4,  239, R, 1,   D4,  479, R, 1,
    D4,  359, R, 121, D4,  239, R, 1,   E4,  239, R, 1,   F4,  479, R, 1,
    F4,  359, R, 121, F4,  239, R, 1,   G4,  239, R, 1,   E4,  479, R, 1,
    E4,  359, R, 121, D4,  239, R, 1,   C4,  239, R, 1,   D4,  719, R, 241,
    A3,  239, R, 1,   C4,  239, R, 1,   D4,  479, R, 1,   D4,  359, R, 121,
    D4,  239, R, 1,   F4,  239, R, 1,   G4,  479, R, 1,   G4,  359, R, 121,
    G4,  239, R, 1,   A4,  239, R, 1,   A4s, 479, R, 1,   A4s, 359, R, 121,
    A4,  239, R, 1,   G4,  239, R, 1,   A4,  239, R, 1,   D4,  479, R, 241,
    D4,  239, R, 1,   E4,  239, R, 1,   F4,  479, R, 1,   F4,  359, R, 121,
    G4,  479, R, 1,   A4,  239, R, 1,   D4,  479, R, 241, D4,  239, R, 1,
    F4,  239, R, 1,   E4,  479, R, 1,   E4,  359, R, 121, F4,  239, R, 1,
    D4,  239, R, 1,   E4,  719, R, 241, A4,  239, R, 1,   C5,  239, R, 1,
    D5,  479, R, 1,   D5,  359, R, 121, D5,  239, R, 1,   E5,  239, R, 1,
    F5,  479, R, 1,   F5,  359, R, 121, F5,  239, R, 1,   G5,  239, R, 1,
    E5,  479, R, 1,   E5,  359, R, 121, D5,  239, R, 1,   C5,  239, R, 1,
    C5,  239, R, 1,   D5,  479, R, 241, A4,  239, R, 1,   C5,  239, R, 1,
    D5,  479, R, 1,   D5,  359, R, 121, D5,  239, R, 1,   E5,  239, R, 1,
    F5,  479, R, 1,   F5,  359, R, 121, F5,  239, R, 1,   G5,  239, R, 1,
    E5,  479, R, 1,   E5,  359, R, 121, D5,  239, R, 1,   C5,  239, R, 1,
    D5,  719, R, 241, A4,  239, R, 1,   C5,  239, R, 1,   D5,  479, R, 1,
    D5,  359, R, 121, D5,  239, R, 1,   F5,  239, R, 1,   G5,  479, R, 1,
    G5,  359, R, 121, G5,  239, R, 1,   A5,  239, R, 1,   A5s, 479, R, 1,
    A5s, 359, R, 121, A5,  239, R, 1,   G5,  239, R, 1,   A5,  239, R, 1,
    D5,  479, R, 241, D5,  239, R, 1,   E5,  239, R, 1,   F5,  479, R, 1,
    F5,  359, R, 121, G5,  479, R, 1,   A5,  239, R, 1,   D5,  479, R, 241,
    D5,  239, R, 1,   F5,  239, R, 1,   E5,  479, R, 1,   E5,  359, R, 121,
    D5,  239, R, 1,   C5s, 239, R, 1,   D5,  479, R, 1,   D5,  359, R, 121,
    E5,  479, R, 1,   F5,  479, R, 1,   F5,  239, R, 1,   F5,  239, R, 1,
    G5,  479, R, 1,   A5,  239, R, 1,   F5,  479, R, 241, F5,  239, R, 1,
    D5,  239, R, 1,   A4,  719, R, 721, A5s, 719, R, 241, G5,  239, R, 1,
    D5,  239, R, 1,   A4s, 719, R, 721, E4,  239, R, 1,   E4,  479, R, 1,
    D4,  719, R, 1,   F4,  719, R, 241, F4,  239, R, 1,   G4,  239, R, 1,
    A4,  479, R, 1,   A4,  359, R, 121, A4,  479, R, 1,   A4s, 239, R, 1,
    A4,  479, R, 721, G4,  479, R, 1,   G4,  359, R, 121, G4,  479, R, 1,
    G4,  239, R, 1,   A4,  479, R, 721, A4,  479, R, 1,   A4,  359, R, 121,
    A4,  479, R, 1,   A4s, 239, R, 1,   A4,  479, R, 721, G4,  479, R, 1,
    F4,  359, R, 121, E4,  479, R, 1,   D4,  719, R, 241, D4,  239, R, 1,
    E4,  239, R, 1,   F4,  839, R, 121, G4,  239, R, 1,   A4,  239, R, 1,
    G4,  479, R, 1,   F4,  359, R, 121, E4,  479, R, 1,   F4,  479, R, 1,
    G4,  359, R, 121, A4,  479, R, 1,   G4,  719, R, 241, F4,  239, R, 1,
    G4,  239, R, 1,   A4,  719, R, 241, G4,  239, R, 1,   F4,  239, R, 1,
    E4,  479, R, 1,   F4,  359, R, 121, E4,  479, R, 1,   D4,  719, R, 241,
    E4,  239, R, 1,   C4,  239, R, 1,   D4,  719, R, 241, D5,  239, R, 1,
    E5,  239, R, 1,   F5,  719, R, 241, E5,  239, R, 1,   F5,  239, R, 1,
    G5,  479, R, 1,   F5,  359, R, 121, G5,  479, R, 1,   A5,  479, R, 1,
    G5,  359, R, 121, F5,  479, R, 1,   D5,  719, R, 241, D5,  239, R, 1,
    E5,  239, R, 1,   F5,  479, R, 1,   G5,  359, R, 121, A5,  479, R, 1,
    A5s, 479, R, 1,   D5,  359, R, 121, G5,  479, R, 1,   F5,  719, R, 241,
    G5,  239, R, 1,   E5,  239, R, 1,   D5,  719, R, 241, E5,  239, R, 1,
    C5s, 239, R, 1,   A5,  719, R, 721, A5s, 719, R, 721, A5,  479, R, 1,
    A5,  359, R, 121, A5,  479, R, 1,   A5,  239, R, 1,   G5,  479, R, 721,
    G5,  719, R, 721, F5,  719, R, 721, F5,  479, R, 1,   G5,  359, R, 121,
    E5,  479, R, 1,   D5,  719, R, 1,   D5,  239, R, 1,   E5,  239, R, 1,
    F5,  239, R, 1,   A5,  719, R, 1,   D5,  239, R, 1,   E5,  239, R, 1,
    F5,  239, R, 1,   A5s, 719, R, 1,   D5,  239, R, 1,   E5,  239, R, 1,
    F5,  239, R, 1,   A5,  479, R, 1,   A5,  359, R, 121, C6,  479, R, 1,
    A5,  239, R, 1,   G5,  479, R, 721, G5,  719, R, 721, F5,  719, R, 721,
    F5,  479, R, 1,   G5,  359, R, 121, E5,  479, R, 1,   D5,  719, R, 721,
    D4,  2159};

u8 v = 100;

static const double s[] = {E3, E3, F3, G3, G3, F3, E3, D3, C3, C3,
                           D3, E3, E3, D3, D3, E3, E3, F3, G3, G3,
                           F3, E3, D3, C3, C3, D3, E3, D3, C3, C3};

int main() {
  microbit::uarte::setBaudrate(microbit::uarte::BaudRate::Baud115200);
  microbit::print("\033[2J\033[H"
                  "\033[1;33m-----------------\033[0m\n\r\033[1;31mmicro:bit "
                  "console\033[0m\n\r\033[1;33m-----------------\033[0m\n\r");
  using namespace microbit;
  v = pins::getAnalog(Pin::PIN_1) / 8;
  runEvery(
      []() {
        v = pins::getAnalog(Pin::PIN_1) / 8;
        print((string)v);
      },
      100000);
  for (u32 i = 0; i < sizeof(x) / sizeof(x[0]); i += 2) {
    if (x[i] == 0) {
      wait(x[i + 1] * 200);
    } else
      sound::tone((u32)x[i], x[i + 1] / 2, v);
  }
  while (1) {
    display::drawImage("happy");
  }
}
