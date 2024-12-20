#ifndef _EASY_VFD
#define _EASY_VFD
#include "Arduino.h"

/*! \mainpage Intro
 * The module uses a pretty high voltage(60V) to power up the VFDs, so be sure to keep it unplugged from the PC when you turn the high-voltage on.
 * (Disconnect VPOWER pin->Flash the code->unplug from the pc->connect external source->connect VPOWER pin)
 */ 

/** @brief The main EasyVFD class**/
class EasyVFD{
    public:

    /** @brief An enum representing supported built-in LED's colors**/
    enum VFDLedColors{
      Blue = 1,
      Green = 2,
      Red = 3,
      White = 4,
      RuB = 5,
      RuG = 6,
      BuG = 7
    };

    /** @brief An enum representing supported types of VFDs**/
    enum VFDType{
      IV22,
      IV6,
      IV11
    };

    /** @brief The microcontroller pin connected to OUT_EN pin of the EasyVFD**/
    uint8_t outputEnable;
    /** @brief The microcontroller pin connected to SHCP pin of the EasyVFD**/
    uint8_t shcp;
    /** @brief The microcontroller pin connected to STCP pin of the EasyVFD**/
    uint8_t stcp;
    /** @brief The microcontroller pin connected to DSIN pin of the EasyVFD**/
    uint8_t dsin;

    /** @brief This constructor takes 4 pin names as arguments, they are labeled OUT_EN, SHCP, STCP and DSIN on your EasyVFD module
     * @param outputEnable The microcontroller pin connected to OUT_EN pin of the EasyVFD
     * @param shcp The microcontroller pin connected to SHCP pin of the EasyVFD.
     * @param stcp The microcontroller pin connected to STCP pin of the EasyVFD.
     * @param dsin The microcontroller pin connected to DSIN pin of the EasyVFD.
      **/
    EasyVFD(uint8_t outputEnable,uint8_t shcp, uint8_t stcp, uint8_t dsin);

    /** @brief Set nixie digit on your EasyVFD. If you have multiple modules connected 'in series' (EasyVFD1 DSOUT->EasyVFD2 DSIN)
    * the value is set to the first module in series(The one which has DSIN connected to the Arduino).
    * To display the value set with this method use the @ref Latch method!
    * @param number The digit you want to display.
    * @param color This argument changes EasyVFDs built-in LED's color. Use @ref VFDLedColors enum values.
    * @param vfd The type of VFD your using. Library is currently supporting IV-11, IV-6 and IV-22.
    * Using differt VFD type may result in wrong pin-out.
    * @param voltage This argument enables the high-voltage convertor, be sure to disconnect the EasyVFD from PC,
    *  when you are calling the function with this argument set to true. You can flash the code with VPOWER pin disconneted,
    *  then disconnect the board from PC, connect to some external power source, then connect the VPOWER pin.
    * @param comma Or the 'decimal point'. This argument controls the decimal point.
    * @param dimming Basically, just PWM on the @ref outputEnable pin. 0 means max brightness, 255 means min brightness.
    **/
    void SetVFD(uint8_t number,VFDLedColors color,VFDType vfd,bool voltage=true,bool comma = false,uint16_t dimming=0);
  
    /** @brief This method 'displays' the digit that you have set using @ref SetVFD, be sure to call it after @ref SetVFD**/
    void Latch(void);

    private:
    
    /** @brief These are inner methods that actualy set the VFDs. Different types of VFDs had a different pinouts. That could be solved by manualy rewiering them
     *   but I decided to solve it by alowing user to pick whitch VFD they're using and than having two different methods for them (IV-6/IV-11 = Type1Setup; IV-22 = Type2Setup)
     *   You can find which bits of shift registers are responsibe for which segments of a VFD in files IV11x6.png and IV22.png in img folder.  
    */
    void _Type1Setup(uint8_t firstShiftRegister, uint8_t secondShiftRegister, uint8_t number);
    void _Type2Setup(uint8_t firstShiftRegister, uint8_t secondShiftRegister, uint8_t number);
};

#endif

