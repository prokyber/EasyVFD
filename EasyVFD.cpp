#include "EasyVFD.h"

EasyVFD::EasyVFD(uint8_t outputEnable,uint8_t shcp, uint8_t stcp, uint8_t dsin):
        outputEnable(outputEnable),
        shcp(shcp),
        stcp(stcp),
        dsin(dsin)
{
    pinMode(outputEnable, OUTPUT);  
    pinMode(shcp, OUTPUT);
    pinMode(stcp, OUTPUT);
    pinMode(dsin, OUTPUT);
}

void EasyVFD::SetVFD(uint8_t number,VFDLedColors color,EasyVFD::VFDType vfd,bool voltage,bool comma,uint16_t dimming){
    #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)//AnalogWrite is supported for some platfroms and not supported for others(Esp32?). if you want to use dimming on these platoforms you have to implement it yourself:)
    analogWrite(outputEnable,dimming);
    #endif
    uint8_t secondShiftRegisterData=0b00011100;
    uint8_t firstShiftRegisterData=0b00000000;
    switch(color)
    {
        case EasyVFD::Red: secondShiftRegisterData&=0b11101111;break;
        case EasyVFD::Green: secondShiftRegisterData&=0b11110111;break;
        case EasyVFD::Blue: secondShiftRegisterData&=0b11111011;break;
        case EasyVFD::White: secondShiftRegisterData&=0b11100011;break;
        case EasyVFD::RuB: secondShiftRegisterData&=0b11101011;break;
        case EasyVFD::RuG: secondShiftRegisterData&=0b11100111;break;
        case EasyVFD::BuG: secondShiftRegisterData&=0b11110011;break;	
    }
    if(voltage)secondShiftRegisterData|=0b00100000;
    if(!comma)firstShiftRegisterData|=0b10000000;
    firstShiftRegisterData &= 0b10000000;
    secondShiftRegisterData &= 0b11111100;
    switch(vfd)
    {
        case EasyVFD::IV6:
        case EasyVFD::IV11:
            this->_Type1Setup(firstShiftRegisterData, secondShiftRegisterData, number);
            break;

        case EasyVFD::IV22:
            this->_Type2Setup(firstShiftRegisterData, secondShiftRegisterData, number);
            break;
    }

}

void EasyVFD::_Type1Setup(uint8_t firstShiftRegisterData, uint8_t secondShiftRegisterData, uint8_t number){
    switch(number){
        case 0:
            firstShiftRegisterData |= 0b00000010;
            break;

        case 1:
            firstShiftRegisterData |= 0b01101111;
            secondShiftRegisterData |= 0b00000010;
            break;

        case 2:
            firstShiftRegisterData |= 0b00000001;
            secondShiftRegisterData |= 0b00000001;
            break;
            
        case 3:
            firstShiftRegisterData |= 0b00000101;
            break;

        case 4:
            firstShiftRegisterData |= 0b00100100;
            secondShiftRegisterData |= 0b00000010;
            break;

        case 5:
            firstShiftRegisterData |= 0b00010100;
            break;

        case 6:
            firstShiftRegisterData |= 0b00010000;
            break;

        case 7:
            firstShiftRegisterData |= 0b00000111;
            secondShiftRegisterData |= 0b00000010;
            break;

        case 8:
            break;

        case 9:
            firstShiftRegisterData |= 0b00000100;
            break;
    }

    shiftOut(dsin, shcp, MSBFIRST, secondShiftRegisterData);
    shiftOut(dsin, shcp, MSBFIRST, firstShiftRegisterData);
}


void EasyVFD::_Type2Setup(uint8_t firstShiftRegisterData, uint8_t secondShiftRegisterData, uint8_t number){
    switch(number){
        case 0:
            secondShiftRegisterData |= 0b00000010;
            break;

        case 1:
            firstShiftRegisterData |= 0b01111110;
            secondShiftRegisterData |= 0b00000010;
            break;

        case 2:
            firstShiftRegisterData |= 0b00010001;
            secondShiftRegisterData |= 0b00000000;
            break;

        case 3:
            firstShiftRegisterData |= 0b00010100;
            break;

        case 4:
            firstShiftRegisterData |= 0b00100110;
            break;

        case 5:
            firstShiftRegisterData |= 0b00000100;
            secondShiftRegisterData |= 0b00000001;
            break;

        case 6:
            secondShiftRegisterData |= 0b00000001;
            break;

        case 7:
            firstShiftRegisterData |= 0b00010110;
            secondShiftRegisterData |= 0b00000010;
            break;
            
        case 8:
            break;

        case 9:
            firstShiftRegisterData |= 0b00000100;
            break;

    }

    shiftOut(dsin, shcp, MSBFIRST, secondShiftRegisterData);
    shiftOut(dsin, shcp, MSBFIRST, firstShiftRegisterData);
}

void EasyVFD::Latch(void){
    digitalWrite(stcp, LOW);
    delay(1);
    digitalWrite(stcp, HIGH);
}


