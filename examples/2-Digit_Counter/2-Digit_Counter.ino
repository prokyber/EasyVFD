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
    for(int j=0; j<10; j++)
    {
      e.SetVFD(i,4,/*Choose IV-Type*/,true,false);
      e.SetVFD(j,4,/*Choose IV-Type*/,true,false);
      e.Latch();
      delay(1000);
    }
  }
}