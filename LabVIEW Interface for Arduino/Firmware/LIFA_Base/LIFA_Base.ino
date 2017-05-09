// 库本路径 C:\Program Files\National Instruments\LabVIEW 2015\vi.lib\LabVIEW Interface for Arduino\Firmware\LIFA_Base

/*********************************************************************************
 **  LVFA_Firmware - Provides Basic Arduino Sketch For Interfacing With LabVIEW.
 *********************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#include "LabVIEWInterface.h" 

void setup()
{  
  // Initialize Serial Port With The Default Baud Rate
  syncLV();

  // Place your custom setup code here
  
}

/*********************************************************************************
 **  loop()
 **
 **  The main loop.  This loop runs continuously on the Arduino.  It 
 **  receives and processes serial commands from LabVIEW.
 **
 **  Input:  None
 **  Output: None
 *********************************************************************************/
void loop()
{   
  // Check for commands from LabVIEW and process them.   
 
  checkForCommand();
  // Place your custom loop code here (this may slow down communication with LabVIEW)
  
  
  if(acqMode==1)
  {
    sampleContinously();
  }

}


