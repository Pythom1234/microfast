#include "microbit.h"
#include "peripheral.h"

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

void on1() {
  microbit::pins::setDigital(Pin::COL_1, 0);
  microbit::pins::setDigital(Pin::ROW_1, 1);
}
void off1() {
  microbit::pins::setDigital(Pin::COL_1, 1);
  microbit::pins::setDigital(Pin::ROW_1, 0);
}

void on2() {
  microbit::pins::setDigital(Pin::COL_5, 0);
  microbit::pins::setDigital(Pin::ROW_1, 1);
}
void off2() {
  microbit::pins::setDigital(Pin::COL_5, 1);
  microbit::pins::setDigital(Pin::ROW_1, 0);
}

void write(u8 reg, u8 val) {
  microbit::i2c::writeBuffer(0x39, (u8[2]){reg, val}, 2);
}

u8 read(u8 reg) {
  microbit::i2c::writeByte(0x39, reg);
  return microbit::i2c::readByte(0x39);
}

u32 i = 0;

void l() {
  microbit::display::drawImage((string)i);
}

int main() {
  microbit::uarte::setBaudrate(microbit::uarte::BaudRate::Baud115200);
  microbit::print("\033[2J\033[H"
                  "\033[1;33m-----------------\033[0m\n\r\033[1;31mmicro:bit "
                  "console\033[0m\n\r\033[1;33m-----------------\033[0m\n\r");
  // microbit::pins::setDigital(Pin::RUN_MIC, 1);
  // float i = 1753;
  // const Pin r[] = {Pin::ROW_1, Pin::ROW_2, Pin::ROW_3, Pin::ROW_4,
  // Pin::ROW_5}; const Pin c[] = {Pin::COL_1, Pin::COL_2, Pin::COL_3,
  // Pin::COL_4, Pin::COL_5}; microbit::pins::setDigital(c[0], 0);
  // microbit::pins::setDigital(c[2], 0);
  // microbit::pins::setDigital(c[4], 0);
  // u32 data[][2] = {};

  // for (u32 i = 0; i < (sizeof(data) / (sizeof(u32) * 2)); i++) {
  //   u32 d = data[i][1] * 40000;
  //   if (data[i][0] == 0)
  //     while (d-- > 0)
  //       microbit::pins::setAnalog(Pin::PIN_0, 0, 1000000.0f / data[i][0]);
  //   else
  //     while (d-- > 0)
  //       microbit::pins::setAnalog(Pin::PIN_0, 5, 1000000.0f / data[i][0]);
  //   u32 x = 5000;
  //   while (x-- > 0)
  //     microbit::pins::setAnalog(Pin::PIN_0, 0, 1000000.0f / 1);
  // }
  // microbit::pins::setDigital(Pin::PIN_0, 0);
  // #define SAMPLES 0xFFFF
  //   i8 data[SAMPLES];
  // string a = "ahojky!";
  // a[1] = 'x';
  // microbit::print(a);
  // asm volatile("bkpt #0");
  // volatile u32* p = (u32*)0xFFFFFFF0;
  // u32 x = *p;
  // asm volatile(".word 0xDEFE");
  using namespace microbit;
  /*
  i2c::init();
  // write(0x80, 0b0);
  write(0x80, 0b11);
  write(0x81, 0b11111100);
  write(0x8F, 0b11001111);
  */
  // oled::init();
  // // i2c::writeByte(oled::ADDR, 0b11010101);
  // // i2c::writeByte(oled::ADDR, 0xFF);
  // // i2c::writeBuffer(oled::ADDR, (u8[2]){0b11010101, 0b1111}, 2);
  // oled::clear(0);
  // oled::drawText(
  //     "test123\nAHOJJJJ!!!\n```python\nprint(\"hello\")\n```\n.......",
  //     0, 0);
  // oled::draw();

  // static Heap<256> hhhhh;
  // void* x = hhhhh.alloc(16);
  // memset(x, 0x11, 16);
  // void* y = hhhhh.alloc(16);
  // memset(y, 0x22, 16);
  // void* y2 = hhhhh.alloc(16);
  // memset(y2, 0x33, 16);
  // hhhhh.free(x);
  // void* z = hhhhh.alloc(16);
  // memset(z, 0x44, 16);
  // void* z2 = hhhhh.alloc(16);
  // memset(z2, 0x55, 16);
  // hhhhh.free(z2);
  // hhhhh.free(y2);
  // void* z3 = hhhhh.alloc(16);
  // memset(z3, 0x66, 16);
  //
  //
  // while (1) {
  //   /*
  //   while (!(read(0x93) & 0x01))
  //       ;

  //   u16 r = read(0x96) | (read(0x97) << 8);
  //   u16 g = read(0x98) | (read(0x99) << 8);
  //   u16 b = read(0x9A) | (read(0x9B) << 8);
  //   */
  //   print((string) "a" + "b");
  //   // + (string) " " + (string)g + (string) " " + (string)b);

  //   // oled::clear(0);
  //   //
  //   oled::drawText("test123\nAHOJJJJ!!!\n```python\nprint(\"hello\")\n```",
  //   // 0,
  //   //                0);
  //   // oled::draw();
  //   // delay(1000000);
  //   // oled::clear(1);
  //   // oled::draw();
  //   // delay(1000000);
  // }
  // microbit::sensors::calibrateCompass();
  // u16 x = 20;
  // radio::init();
  // u8* t = (u8*)calloc(32, 1);
  // i8 i = 1;
  bool ap = false;
  bool bp = false;
  runEvery(l, 2000);
  // runAfter([]() { print("1"); }, 1000000);
  // wait(1000000);
  // runAfter([]() { print("2"); }, 1000000);
  // wait(1000000);
  while (1) {
    if (sensors::buttonA()) {
      if (!ap)
        i--;
      // ap = true;
    } else {
      ap = false;
    }
    if (sensors::buttonB()) {
      if (!bp)
        i++;
      // bp = true;
    } else {
      bp = false;
    }
    // i++;
    if (i == 25)
      i = 1;
    if (i == 0)
      i = 24;
    // if (!pins::getDigital(Pin::BUTTON_A)) {
    //   t[0] = 'A';
    //   radio::send(t);
    // }
    // if (!pins::getDigital(Pin::BUTTON_B)) {
    //   t[0] = 'B';
    //   radio::send(t);
    // }
    // u8* m = radio::recieve(100);
    // off1();
    // off2();
    // if (m != nullptr) {
    //   print((string)radio::getSignalStrength());
    //   if (m[0] == 'A') {
    //     on1();
    //   }
    //   if (m[0] == 'B') {
    //     on2();
    //   }
    //   free(m);
    // }
    // u16 x = microbit::pins::getAnalog(PIN_1);
    // for (u32 i = 0; i < 8; i++)
    //   microbit::sound::tone(song[i], 100, 0);
    // for (u32 i = 0; i < 30000; i++)
    //   microbit::pins::setAnalog(PIN_16, x, 20000);
    // for (u32 i = 0; i < 30000; i++)
    //   microbit::pins::setAnalog(PIN_15, x, 20000);
    // for (u32 i = 0; i < 30000; i++)
    //   microbit::pins::setAnalog(PIN_14, x, 20000);
    // for (u32 i = 0; i < 30000; i++)
    //   microbit::pins::setAnalog(PIN_13, x, 20000);

    // // microbit::pins::setAnalog(SPEAKER, x / 2, x);
    // // microbit::pins::setAnalog(PIN_16, x, 20000);
    // // microbit::pins::setAnalog(PIN_14, x, 20000);
    // // microbit::pins::setAnalog(PIN_15, x, 20000);
    // // microbit::pins::setAnalog(PIN_13, x, 20000);
    // print((string)x);
    // delay(500000);
    // x += 5;
    // if (x == 140)
    //   x = 20;
    // string a = x;
    // a.push('x', -3);
    // string b = a;
    // b.pop(-1);
    // b.push('_', -1);
    // b[2] = '_';
    // microbit::print(a + "ahoj");
    // microbit::print((string)(50.0001f * x));
    // microbit::print(a + " = " + b);
    // microbit::print((string) "." * x);
    // microbit::print("(string)(u32)microbit::rnd()");
    // auto f = sensors::magnetometer();
    // microbit::print((string)f.x + " " + (string)f.y + " " + (string)f.z + "
    // ");
    // microbit::print((string)microbit::sensors::compass());
    // microbit::print((string)f.x);
    // microbit::print(string(f.x, 10));
    // microbit::print((string)(0.555f));
    // microbit::print((string)0.000000000000000000000000000000000000011754942f);
    // microbit::print((string)5.10000000000001000000750000004940000000002f);
    // microbit::print((string)340282350000000000000000000000000000000.0f);
    // microbit::print(microbit::input(">>> "));
    // const char *x = microbit::input("> ");
    // if (x[1] == '\b') {
    //   microbit::print("x[1] == '\\b'", "\n\r\0");
    // }
    // string<100> a = -9223372036854775807;
    // u16 a = microbit::sound::microphone();
    // for (u8 z = 0; z < 5; z++)
    /*
    microbit::pins::setAnalog(r[0], i);
    microbit::pins::setAnalog(r[2], i);
    microbit::pins::setAnalog(r[4], i);
    */
    // microbit::pins::setDigital(r[0], 1);
    // microbit::pins::setDigital(r[2], 1);
    // microbit::pins::setDigital(r[4], 1);
    // i = microbit::pins::getAnalog(Pin::PIN_1);
    // microbit::pins::setAnalog(Pin::PIN_0, 10, 1000000.0f / i);
    // string<20> x = i;
    // microbit::print(x);
    // string<100> x = a;
    // microbit::uart::startRX();
    // char x = microbit::uart::read(1);
    // microbit::uart::stopRX();
    // microbit::print(a.c_str());
    // if (x == 'c') {
    // }

    // on1();
    // for (u32 x = 0; x < SAMPLES; x++) {
    //   // #define NUM 1
    //   //       i32 sum = 0;
    //   //       for (u8 h = 0; h < NUM; h++) {
    //   //         i8 z = microbit::sensors::microphone();
    //   //         sum += z;
    //   //       }
    //   //       i8 y = sum / NUM;
    //   // if (abs(y) < 20)
    //   //   y = 0;
    //   data[x] = (microbit::sensors::microphone() / 8) + 128;
    //   delay(80);
    // }
    // off1();

    // on2();
    // for (u32 x = 0; x < SAMPLES; x++) {
    //   microbit::pins::setAnalog(Pin::SPEAKER, (6 * data[x]) + 256, 64);
    //   delay(180);
    // }
    // off2();
    // string<20> s = (u32)data[0x8888];
    // microbit::print(s.c_str());
    // if (!microbit::pins::getDigital(Pin::BUTTON_A)) {
    //   if (i > 0)
    //     i -= 0.01;
    // }
    // if (!microbit::pins::getDigital(Pin::BUTTON_B)) {
    //   // if (i < 1023)
    //   i += 0.01;
    // }
  }
}
