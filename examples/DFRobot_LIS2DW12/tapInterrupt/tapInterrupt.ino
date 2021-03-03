/**！
 * @file tapInterrupt.ino
 * @brief Click interrupt detection
 * @n 在使用SPI时,片选引脚 可以通过改变宏IIS2DLPC_CS的值修改
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_LIS2DW12
 */


#include <DFRobot_LIS2DW12.h>

//当你使用I2C通信时,使用下面这段程序,使用DFRobot_LIS2DW12_I2C构造对象
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
DFRobot_LIS2DW12_I2C acce/*(&Wire,0x19)*/;


//当你使用SPI通信时,使用下面这段程序,使用DFRobot_LIS2DW12_SPI构造对象
#if defined(ESP32) || defined(ESP8266)
#define LIS2DW12_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define LIS2DW12_CS 3
#elif (defined NRF5)
#define LIS2DW12_CS P3
#endif
/*!
 * @brief Constructor 
 * @param cs  Chip selection pinChip selection pin
 * @param spi SPI controller
 */
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS);
volatile uint8_t intFlag = 0;
void interEvent(){
  intFlag = 1;
}


void setup(void){

  Serial.begin(9600);
  while(acce.begin()){
     delay(1000);
     Serial.println("通信失败，请检查连线是否准确");
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  //Chip soft reset
  acce.softReset();
  #if defined(ESP32) || defined(ESP8266)||defined(ARDUINO_SAM_ZERO)
  attachInterrupt(digitalPinToInterrupt(D6)/*Query the interrupt number of the D6 pin*/,interEvent,CHANGE);
  #else
  /*    The Correspondence Table of AVR Series Arduino Interrupt Pins And Terminal Numbers
   * ---------------------------------------------------------------------------------------
   * |                                        |  DigitalPin  | 2  | 3  |                   |
   * |    Uno, Nano, Mini, other 328-based    |--------------------------------------------|
   * |                                        | Interrupt No | 0  | 1  |                   |
   * |-------------------------------------------------------------------------------------|
   * |                                        |    Pin       | 2  | 3  | 21 | 20 | 19 | 18 |
   * |               Mega2560                 |--------------------------------------------|
   * |                                        | Interrupt No | 0  | 1  | 2  | 3  | 4  | 5  |
   * |-------------------------------------------------------------------------------------|
   * |                                        |    Pin       | 3  | 2  | 0  | 1  | 7  |    |
   * |    Leonardo, other 32u4-based          |--------------------------------------------|
   * |                                        | Interrupt No | 0  | 1  | 2  | 3  | 4  |    |
   * |--------------------------------------------------------------------------------------
   */
  /*                      The Correspondence Table of micro:bit Interrupt Pins And Terminal Numbers
   * ---------------------------------------------------------------------------------------------------------------------------------------------
   * |             micro:bit                       | DigitalPin |P0-P20 can be used as an external interrupt                                     |
   * |  (When using as an external interrupt,      |---------------------------------------------------------------------------------------------|
   * |no need to set it to input mode with pinMode)|Interrupt No|Interrupt number is a pin digital value, such as P0 interrupt number 0, P1 is 1 |
   * |-------------------------------------------------------------------------------------------------------------------------------------------|
   */
  attachInterrupt(/*Interrupt No*/0,interEvent,CHANGE);//Open the external interrupt 0, connect INT1/2 to the digital pin of the main control: 
     //UNO(2), Mega2560(2), Leonardo(3), microbit(P0).
  #endif
  
  /**！
    Set the sensor measurement range:
                   e2_g   /<±2g>/
                   e4_g   /<±4g>/
                   e8_g   /<±8g>/
                   e16_g  /< ±16g>/
  */
  acce.setRange(DFRobot_LIS2DW12::e2_g);
  
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
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise_12bit);

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
  acce.setDataRate(DFRobot_LIS2DW12::eOdr_800hz);
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
  // |                                       参数与时间之间的线性关系                                         |
  // |--------------------------------------------------------------------------------------------------------|
  // |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
  // |   dur          |Data rate = 25 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 800 Hz  |
  // |--------------------------------------------------------------------------------------------------------|
  // |  n             |n*(1s/25)= n*40ms|  n*(1s/100)= n*10ms  |  n*(1s/400)= n*2.5ms |  n*(1s/800)= n*1.25ms |
  // |--------------------------------------------------------------------------------------------------------|
  acce.setTapDur(7);
  
  /**！
    Set click detection mode:
    eOnlySingle(single click)
    eBothSingleDouble(Single click and double click)
  */
  acce.setTapMode(DFRobot_LIS2DW12::eBothSingleDouble);
  
  /**！
    Set the interrupt source of the int1 pin:
    eDoubleTap(Double click)
    eFfEvent(Free fall)
    eWakeupEvent(wake)
    eSingleTap(single-Click)
    eTnt16d(Orientation change check)
  */

  acce.setPinInt1Route(DFRobot_LIS2DW12::eSingleTap);
  acce.setPinInt1Route(DFRobot_LIS2DW12::eDoubleTap);
  delay(1000);
}

void loop(void){
  if(intFlag == 1){
    //Click detected
    DFRobot_LIS2DW12:: eTap_t tapEvent = acce.tapDetect();
    //点击方向的源头检测
    DFRobot_LIS2DW12::eTapDir_t dir = acce.getTapDirection();
    if(tapEvent  == DFRobot_LIS2DW12::eSingleClick){
        Serial.print("single click Detected :");
    }
    if(tapEvent  == DFRobot_LIS2DW12::eDoubleClick){  
        Serial.print("Double Tap Detected :");
    }
    
    if(dir == DFRobot_LIS2DW12::eDirXup){
      Serial.println("Click it in the positive direction of x");
    }else if(dir == DFRobot_LIS2DW12::eDirXdown){
      Serial.println("Click it in the negative direction of x");
    }else if(dir == DFRobot_LIS2DW12::eDirYup){
      Serial.println("Click it in the positive direction of y");
    }else if(dir == DFRobot_LIS2DW12::eDirYdown){
      Serial.println("Click it in the negative direction of y");
    }else if(dir == DFRobot_LIS2DW12::eDirZup){
      Serial.println("Click it in the positive direction of z");
    }else if(dir == DFRobot_LIS2DW12::eDirZdown){
      Serial.println("Click it in the negative direction of z");
    }
    
    intFlag = 0;
    
    }
}