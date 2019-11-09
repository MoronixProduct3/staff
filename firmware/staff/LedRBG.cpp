#include "LedRGB.h"

int LedRGB::nextChannel = 0;

LedRGB::LedRGB()
{
  m_redChannel = nextChannel ++;
  m_greenChannel = nextChannel ++;
  m_blueChannel = nextChannel ++;
}

void LedRGB::begin(int redPin, int greenPin, int bluePin, const Color & initialColor)
{
  ledcSetup(m_redChannel, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(m_greenChannel, 12000, 8);
  ledcSetup(m_blueChannel, 12000, 8);

  ledcAttachPin(redPin, m_redChannel);
  ledcAttachPin(greenPin, m_greenChannel);
  ledcAttachPin(bluePin, m_blueChannel);

  write(initialColor);
}

void LedRGB::write(const Color & newColor, float fade)
{
  // Active low outputs
  ledcWrite(m_redChannel, 255 - byte(newColor.r * fade));
  ledcWrite(m_greenChannel, 255 - byte(newColor.g * fade));
  ledcWrite(m_blueChannel, 255 - byte(newColor.b * fade));
}
