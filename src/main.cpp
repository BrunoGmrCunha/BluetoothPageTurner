#include <Arduino.h>

#include <BleKeyboard.h>
//Test Line
BleKeyboard bleKeyboard;

const int pinNumber = 27;
bool pressed = false;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  bleKeyboard.deviceName = "BLUETOOTH_KEYBOARD";

  bleKeyboard.begin();
  pinMode(pinNumber, INPUT_PULLUP);
  //attachInterrupt(pinNumber, pressed, CHANGE);
}

void loop()
{

  if (bleKeyboard.isConnected())
  {

    unsigned long time = millis();
    unsigned long currentTime = time;
    while (digitalRead(pinNumber) && currentTime - time <= 500)
    {
      currentTime = millis();
      pressed = true;
      delay(10);
    }
    if (pressed)
    {
      if (currentTime - time >= 200)
      {
        Serial.println("Esquerda");
        bleKeyboard.write(KEY_LEFT_ARROW);
        pressed = false;
      }
      else if ((currentTime - time < 200))
      {
        Serial.println("Direita");
        bleKeyboard.write(KEY_RIGHT_ARROW);
        pressed = false;
      }

      delay(500);
    }
  }
}