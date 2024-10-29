#ifndef _EASY_VFD
#define _EASY_VFD
#include "Arduino.h"

/*! \mainpage Intro
 * This is a little documentation for the EasyNixie module, before using the module be sure to checkout all the safety guidelines located at:
 * https://www.kickstarter.com/projects/esp32-stick/easynixie. 
 * The module uses a pretty high voltage(200V) to power up the nixies, so be sure to keep it unplugged from the PC when you turn the high-voltage on.
 * (Disconnect VPOWER pin->Flash the code->unplug from the pc->connect external source->connect VPOWER pin)
 */ 

/** @defgroup Colors Avalilable led colors
 *  @{
 */
#define EASY_VFD_BLUE 1
#define EASY_VFD_GREEN 2
#define EASY_VFD_RED 3
#define EASY_VFD_WHITE 4
#define EASY_VFD_RuB 5
#define EASY_VFD_RuG 6
#define EASY_VFD_BuG 7
/** @} */

/** @brief The main EasyVFD class**/
class EasyVFD{
    public:

    enum VFDType{
      IV22,
      IV6,
      IV11
    };

    /** @brief The microcontroller pin connected to OUT_EN pin of the EasyNixie**/
    uint8_t outputEnable;
    /** @brief The microcontroller pin connected to SHCP pin of the EasyNixie**/
    uint8_t shcp;
    /** @brief The microcontroller pin connected to STCP pin of the EasyNixie**/
    uint8_t stcp;
    /** @brief The microcontroller pin connected to DSIN pin of the EasyNixie**/
    uint8_t dsin;

    /** @brief This constructor takes 4 pin names as arguments, they are labeled OUT_EN, SHCP, STCP and DSIN on your EasyNixie module
     * @param outputEnable The microcontroller pin connected to OUT_EN pin of the EasyNixie
     * @param shcp The microcontroller pin connected to SHCP pin of the EasyNixie.
     * @param stcp The microcontroller pin connected to STCP pin of the EasyNixie.
     * @param dsin The microcontroller pin connected to DSIN pin of the EasyNixie.
      **/
    EasyVFD(uint8_t outputEnable,uint8_t shcp, uint8_t stcp, uint8_t dsin);

    /** @brief Set nixie digit/symbol on your EasyNixie. If you have multiple modules connected 'in series' (EasyNixie1 DSOUT->EasyNixie2 DSIN)
    * the value is set to the first module in series(The one which has DSIN connected to the Arduino).
    * To display the value set with this method use the @ref Latch method!
    * @param number The digit/symbol you want to display. The digits can be swapped if you are using non-standard nixies(not In-12/In-17).
    * @param color Led color, checkout the \ref Colors, I should have probably used enum to avoid illegal arguments, 
    * but I am too lazy to rewrite and retest all the examples...
    * @param voltage This argument enables the high-voltage convertor, be sure to disconnect the EasyNixie from PC,
    *  when you are calling the function with this argument set to true. You can flash the code with VPOWER pin disconneted,
    *  then disconnect the board from PC, connect to some external power source, then connect the VPOWER pin.
    * @param comma Or the 'decimal point'. This argument controls the decimal point of In-12B.
    * @param dimming Basically, just PWM on the @ref outputEnable pin. 0 means max brightness, 255 means min brightness.
    **/
    void SetVFD(uint8_t number,uint8_t color,VFDType vfd,bool voltage=true,bool comma = false,uint16_t dimming=0);
  
    /** @brief This method 'displays' the digit that you have set using @ref SetNixie, be sure to call it after @ref SetNixie**/
    void Latch(void);

    private:
    
    void _Type1Setup(uint8_t firstShiftRegister, uint8_t secondShiftRegister, uint8_t number);
    void _Type2Setup(uint8_t firstShiftRegister, uint8_t secondShiftRegister, uint8_t number);
};

#endif

