#include <cmath>
#include <algorithm>
#include "Color.h"

Color Color::hex(const char * hexColor)
{
  uint8_t offset = 0;

  if (hexColor[0] == '#')
    offset = 1;

  return Color(
           hexDecode(hexColor + offset),
           hexDecode(hexColor + offset + 2),
           hexDecode(hexColor + offset + 4));
}

Color Color::hsv(float h, float s, float v)
{
  // fixing inputs
  h = std::fmod(h, 360);
  if (h < 0)
    h += 360;
  s = std::max(0.0f, std::min(1.0f, s));  // replace with std::clamp when cpp17 is used
  v = std::max(0.0f, std::min(1.0f, v));

  float c = v * s;
  float x = c * (1 - std::abs(std::fmod(h / 60, 2) - 1));
  float m = v - c;

  float tr, tg, tb;

  if (h < 60) {
    tr = c;
    tg = x;
    tb = 0;
  }
  else if (h < 120) {
    tr = x;
    tg = c;
    tb = 0;
  }
  else if (h < 180) {
    tr = 0;
    tg = c;
    tb = x;
  }
  else if (h < 240) {
    tr = 0;
    tg = x;
    tb = c;
  }
  else if (h < 300) {
    tr = x;
    tg = 0;
    tb = c;
  }
  else {
    tr = c;
    tg = 0;
    tb = x;
  }

  return Color(
           uint8_t(255 * (tr + m)),
           uint8_t(255 * (tg + m)),
           uint8_t(255 * (tb + m)));
}

uint8_t Color::hexDecode(const char * hexPair)
{
  uint8_t sum = 0;

  for (uint8_t i = 0; i < 2; ++i)
  {
    sum = sum << 4;

    uint8_t charValue = 0;
    if (hexPair[i] >= 'a' && hexPair[i] <= 'f')
      charValue = hexPair[i] - 'a' + 10;
    else if (hexPair[i] >= 'A' && hexPair[i] <= 'F')
      charValue = hexPair[i] - 'A' + 10;
    else if (hexPair[i] >= '0' && hexPair[i] <= '9')
      charValue = hexPair[i] - '0';

    sum += charValue;
  }

  return sum;
}
