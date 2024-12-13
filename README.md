# EasyVFD Library

The EasyVFD library  allows you to control VFDs with an EasyVFD module along with its built-in RGB LED. Currently, it supports IV-11, IV-22, and IV-6 type VFDs.

## All user enums

- VFDLedColors
- VFDType

## VFDLedColors

Represents the built-in LED colors available for the EasyVFD.

### Values

- **Blue**
- **Green**
- **Red**
- **White**
- **RuB** *(Purple)*
- **RuG** *(Yellow)*
- **BuG** *(Cyan)*

## VFDType

Represents the types of VFDs supported by the library.

### Value

- **IV22**
- **IV6**
- **IV11**

## All user metohds

- EasyVDF
- SetVDF
- Latch

## EasyVDF

Constructor to initialize the EasyVFD object with the required pin connections.

### Parameters

- uint8_t outputEnable - number of pin that enables voltage on the desk
- uint8_t shcp - number of shcp pin
- uint8_t stcp - number of stcp pin
- uint8_t dsin - number of data input pin

## SetVFD()

Sets the digit to display on the VFD, changes the LED color, and optionally controls the voltage, decimal point, and brightness.

### Parameters

- `uint8_t number` - The digit to display on the VFD.
- `VFDLedColors color` - The color for the VFD's built-in LED. Use values from `VFDLedColors` enum.
- `VFDType vfd` - The type of VFD being used. Use values from `VFDType` enum.
- `bool voltage` - (Optional) Enables the high-voltage converter. Make sure to disconnect the EasyVFD from the PC when enabling this. (default value = `true`)
- `bool comma`- (Optional) Controls whether the decimal point is shown. (default value = `false`)
- `uint16_t dimming`: (Optional) The dimming level for the LEDs (if applicable)

### Call example

("e" is an EasyVFDD instance)

```cpp
e.SetVFDD(8, EasyVFD::Red, true, true);
```

This will set number 8 to be displayed on the VFD, changes LED color to red, turns ON decimal point and enables high-voltage in shift register. Don't forget to call Latch method afterward to apply the changes on the module.

## Latch

Displays the previously set digit on the VFD. This must be called after `SetVFD` to apply the changes.

### Call example

("e" is an EasyVFDD instance)

```cpp
e.SetVFDD(/*your values*/);
e.Latch();
```

## Notes

- **High Voltage Caution**:  
The EasyVFD module operates at high voltage (60V), so always ensure the module is unplugged from the PC when turning on the high voltage. The suggested procedure is to disconnect the `VPOWER` pin, flash the code, unplug from the PC, connect an external power source, and then reconnect the `VPOWER` pin.

- **Pinout Configurations**:  
Different VFD types have different pinouts, which are handled in the private setup methods (`_Type1Setup` and `_Type2Setup`). You can find the pin-to-segment mappings for each VFD type in the images `IV11x6.png` and `IV22.png` in the `img` folder.
