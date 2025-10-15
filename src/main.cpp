#include "microbit.h"

inline volatile void delay(volatile u32 cycles) {
  while (cycles--)
    ;
}

#define C2 65.41
#define C2s 69.30
#define D2b 69.30
#define D2 73.42
#define D2s 77.78
#define E2b 77.78
#define E2 82.41
#define F2 87.31
#define F2s 92.50
#define G2b 92.50
#define G2 98.00
#define G2s 103.83
#define A2b 103.83
#define A2 110.00
#define A2s 116.54
#define B2b 116.54
#define B2 123.47

#define C3 130.81
#define C3s 138.59
#define D3b 138.59
#define D3 146.83
#define D3s 155.56
#define E3b 155.56
#define E3 164.81
#define F3 174.61
#define F3s 185.00
#define G3b 185.00
#define G3 196.00
#define G3s 207.65
#define A3b 207.65
#define A3 220.00
#define A3s 233.08
#define B3b 233.08
#define B3 246.94

#define C4 261.63
#define C4s 277.18
#define D4b 277.18
#define D4 293.66
#define D4s 311.13
#define E4b 311.13
#define E4 329.63
#define F4 349.23
#define F4s 369.99
#define G4b 369.99
#define G4 392.00
#define G4s 415.30
#define A4b 415.30
#define A4 440.00
#define A4s 466.16
#define B4b 466.16
#define B4 493.88

#define C5 523.25
#define C5s 554.37
#define D5b 554.37
#define D5 587.33
#define D5s 622.25
#define E5b 622.25
#define E5 659.26
#define F5 698.46
#define F5s 739.99
#define G5b 739.99
#define G5 783.99
#define G5s 830.61
#define A5b 830.61
#define A5 880.00
#define A5s 932.33
#define B5b 932.33
#define B5 987.77

#define C6 1046.50
#define C6s 1108.73
#define D6b 1108.73
#define D6 1174.66
#define D6s 1244.51
#define E6b 1244.51
#define E6 1318.51
#define F6 1396.91
#define F6s 1479.98
#define G6b 1479.98
#define G6 1567.98
#define G6s 1661.22
#define A6b 1661.22
#define A6 1760.00
#define A6s 1864.66
#define B6b 1864.66
#define B6 1975.53

int main() {
  microbit::uarte::setBaudrate(microbit::uarte::BaudRate::Baud115200);
  microbit::print("\033[2J\033[H"
                  "\033[1;33m-----------------\033[0m\n\r\033[1;31mmicro:bit "
                  "console\033[0m\n\r\033[1;33m-----------------\033[0m\n\r");
  using namespace microbit;
  while (1) {
    sound::tone(C4, 100);
    // pins::setDigital(Pin::SPEAKER, 1);
    // wait(5);
    // pins::setDigital(Pin::SPEAKER, 0);
    // wait(5);
    // display::drawImage("happy");
  }
}
