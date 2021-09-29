#include <Arduino.h>

#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Keyboard", "BRUNO CUNHA", 100);

const int pinNumber = 27;
bool pressed = false;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  pinMode(pinNumber, INPUT_PULLUP);
  bleKeyboard.begin();
  bleKeyboard.setName("Keyboad");
  //attachInterrupt(pinNumber, pressed, CHANGE);
}

void loop()
{
  if (bleKeyboard.isConnected())
  {
    if (digitalRead(pinNumber))
    {
      int counter = 0;
      while (digitalRead(pinNumber) && counter <= 250)
      {
        counter++;
        delay(1);
      }
      if (counter > 100)
      {
        if (counter >= 300)
        {
          Serial.println("Esquerda");
          bleKeyboard.write(KEY_LEFT_ARROW);
          pressed = false;
        }
        else
        {
          Serial.println("Direita");
          bleKeyboard.write(KEY_RIGHT_ARROW);
          pressed = false;
        }
        delay(500);
      }
    }
  }
}
