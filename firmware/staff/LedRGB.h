#ifndef LED_RGB_H
#define LED_RGB_H

#include <Arduino.h>
#include "Color.h"

class LedRGB
{
  public:
    LedRGB();

    void begin(int redPin, int greenPin, int bluePin, const Color & initialColor = Color(0, 0, 0));

    void write(const Color & newColor, float fade = 1);

  private:
    static int nextChannel;

    int
    m_redChannel,
    m_greenChannel,
    m_blueChannel;
};

#endif /* LED_RGB_H */
