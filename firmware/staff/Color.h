#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

struct Color
{
  public:
    uint8_t r, g, b;

    Color(uint8_t ir, uint8_t ig, uint8_t ib):
      r(ir), g(ig), b(ib)
    {}

    static Color hex(const char * hexColor);
    static Color hsv(float h, float s, float v);

  private:
    static uint8_t hexDecode(const char * hexPair);
};

#endif /* COLOR_H */
