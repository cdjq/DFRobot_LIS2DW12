/**！
 * @file tapInterrupt.ino
 * @brief Click interrupt detection
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_DFRobot_IIS2DLPC
 */


#include <DFRobot_IIS2DLPC.h>

//当你使用I2C通信时,使用下面这段程序,使用DFRobot_IIS2DLPC_I2C构造对象
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
DFRobot_IIS2DLPC_I2C acce/*(&Wire,0x19)*/;


//当你使用SPI通信时,使用下面这段程序,使用DFRobot_IIS2DLPC_SPI构造对象
#if defined(ESP32) || defined(ESP8266)
#define IIS2DLPC_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define IIS2DLPC_CS 3
#elif (defined NRF5)
#define IIS2DLPC_CS P3
#endif
/*!
 * @brief Constructor 
 * @param cs : Chip selection pinChip selection pin
 * @param spi :SPI controller
 */
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS);
volatile int intFlag = 0;
void interEvent(){
  intFlag = 1;
}


void setup(void){

  Serial.begin(9600);
  while(acce.begin()){
     delay(1000);
     Serial.println("init failure");
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  //Chip soft reset
  acce.softReset();
  //Interrupt setting, open when using interrupt
  attachInterrupt(0,interEvent, CHANGE);
  
  /**！
    Set the sensor measurement range:
                   e2_g   /<±2g>/
                   e4_g   /<±4g>/
                   e8_g   /<±8g>/
                   e16_g  /< ±16g>/
  */
  acce.setRange(DFRobot_IIS2DLPC::e2_g);
  
  /**！
   Set power mode:
      eHighPerformance              /<High-Performance Mode>/
      eContLowPwr_4                /<Continuous measurement,Low-Power Mode 4(14-bit resolution)>/
      eContLowPwr_3                /<Continuous measurement,Low-Power Mode 3(14-bit resolution)>/
      eContLowPwr_2                /<Continuous measurement,Low-Power Mode 2(14-bit resolution)>/
      eContLowPwr_12bit            /<Continuous measurement,Low-Power Mode 1(12-bit resolution)>/
      eSingleLowPwr_4              /<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>/
      eSingleLowPwr_3              /<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>/
      eSingleLowPwr_2              /<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>/
      eSingleLowPwr_12bit          /<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>/
      eHighPerformanceLowNoise     /<High-Performance Mode,Low-noise enabled>/
      eContLowPwrLowNoise_4        /<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>/
      eContLowPwrLowNoise_3        /<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>/
      eContLowPwrLowNoise_2        /<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>/
      eContLowPwrLowNoise_12bit    /<Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)>/
      eSingleLowPwrLowNoise_4         /<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>/
      eSingleLowPwrLowNoise_3         /<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>/
      eSingleLowPwrLowNoise_2         /<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>/
      eSingleLowLowNoisePwr_12bit     /<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>/
  */
  acce.setPowerMode(DFRobot_IIS2DLPC::eContLowPwrLowNoise_12bit);

  /**！
    Set the sensor data collection rate:
    eOdr_0hz         
    eOdr_1hz6_lp_only
    eOdr_12hz5       
    eOdr_25hz        
    eOdr_50hz        
    eOdr_100hz       
    eOdr_200hz       
    eOdr_400hz       
    eOdr_800hz       
    eOdr_1k6hz       
    eSetSwTrig       
    eSetPinTrig      
  */
  acce.setDataRate(DFRobot_IIS2DLPC::eOdr_800hz);
  //Enable click detection in the X direction
  acce.enableTapDetectionOnZ(true);
  //Enable click detection in Y direction
  acce.enableTapDetectionOnY(true);
  //Enable click detection in the Z direction
  acce.enableTapDetectionOnX(true);
  //The threshold setting in the X direction 
  //Threshold(g),Can only be used in the range of ±2g
  acce.setTapThresholdOnX(/*Threshold = */0.2);
  //The threshold setting in the Y direction   //Threshold(g),Can only be used in the range of ±2g
  acce.setTapThresholdOnY(/*Threshold = */0.2);
  //The threshold setting in the Z direction   //Threshold(g),Can only be used in the range of ±2g)
  acce.setTapThresholdOnZ(/*Threshold = */0.2);
  
  //Set the interval of double-clicking, 1 LSB = 32 * 1/ODR (0~15) (data acquisition frequency)
  acce.setTapDur(7);
  
  /**！
    Set click detection mode:
    eOnlySingle(single click)
    eBothSingleDouble(Single click and double click)
  */
  acce.setTapMode(DFRobot_IIS2DLPC::eBothSingleDouble);
  
  /**！
    Set the interrupt source of the int1 pin:
    eDoubleTap(Double click)
    eFfEvent(Free fall)
    eWakeupEvent(wake)
    eSingleTap(single-Click)
    eTnt16d(Orientation change check)
  */

  acce.setPinInt1Route(DFRobot_IIS2DLPC::eSingleTap);
  acce.setPinInt1Route(DFRobot_IIS2DLPC::eDoubleTap);
  delay(1000);
}

void loop(void){
  if(intFlag == 1){
   //Click detected
     DFRobot_IIS2DLPC:: eTap_t tapEvent = acce.tapDetect();
     DFRobot_IIS2DLPC::eTapDir_t dir = acce.getTapDirection();
     if(tapEvent  == DFRobot_IIS2DLPC::eSingleClick){
         Serial.print("single click Detected :");
     }
     if(tapEvent  == DFRobot_IIS2DLPC::eDoubleClick){  
         Serial.print("Double Tap Detected :");
     }
     
     if(dir == DFRobot_IIS2DLPC::eDirXup){
       Serial.println("Click it in the positive direction of x");
     }else if(dir == DFRobot_IIS2DLPC::eDirXdown){
       Serial.println("Click it in the negative direction of x");
     }else if(dir == DFRobot_IIS2DLPC::eDirYup){
       Serial.println("Click it in the positive direction of y");
     }else if(dir == DFRobot_IIS2DLPC::eDirYdown){
       Serial.println("Click it in the negative direction of y");
     }else if(dir == DFRobot_IIS2DLPC::eDirZup){
       Serial.println("Click it in the positive direction of z");
     }else if(dir == DFRobot_IIS2DLPC::eDirZdown){
       Serial.println("Click it in the negative direction of z");
     }
     
     intFlag = 0;
   
  }
}