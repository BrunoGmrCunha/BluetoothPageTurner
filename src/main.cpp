#include <Arduino.h>

#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Keyboard", "BRUNO CUNHA", 100);

const int left = 16;
const int right = 17;

bool pressedLeft = false;
bool pressedRight = false;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  pinMode(left, INPUT);
  pinMode(right, INPUT);

  bleKeyboard.begin();
  bleKeyboard.setName("Organ Page Turner");
  // attachInterrupt(pinNumber, pressed, CHANGE);
}

void loop()
{

  if (bleKeyboard.isConnected())
  {

    unsigned long time = millis();
    unsigned long currentTime = time;
    while (digitalRead(left) && currentTime - time <= 20)
    {
      currentTime = millis();
      pressedLeft = true;
      delay(10);
    }
     while (digitalRead(right) && currentTime - time <= 20)
    {
      currentTime = millis();
      pressedRight = true;
      delay(10);
    }

    if (pressedLeft)
    {
      if (currentTime - time >= 20)
      {
        Serial.println("Esquerda");
        bleKeyboard.write(KEY_LEFT_ARROW);
        pressedLeft = false;
      }
      delay(500);
    }
    else if (pressedRight)
    {
      if (currentTime - time >= 20)
      {
        Serial.println("DIREITA");
        bleKeyboard.write(KEY_RIGHT_ARROW);
        pressedRight = false;
      }
      delay(500);
    }
  }
}

