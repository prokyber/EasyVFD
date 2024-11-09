#include <Arduino.h>
#include <EasyVFD.h>

EasyVFD e(3,2,6,7);

void setup() 
{
}

void loop()
{
  for(int i=0; i<10; i++)
  {
    e.SetVFD(i,4, EasyVFD::IV22, true, false);
    e.Latch();
    delay(1000);
  }
}