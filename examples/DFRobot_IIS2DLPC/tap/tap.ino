/**！
 * @file tap.ino
 * @brief Single click and double click detection,点击模块，或者点击模块附件的桌面都可以触发点击事件
 * @n 可以通过setTapMode()函数选择只检测单击，或单击和双击同时检测
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
 * @param cs Chip selection pinChip selection pin
 * @param spi SPI controller
 */
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS,&SPI);
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS);

void setup(void){

  Serial.begin(9600);
  while(acce.begin()){
     delay(1000);
     Serial.println("通信失败，请检查连线是否准确,使用I2C通信时检查地址是否设置准确");
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  //Chip soft reset
  acce.softReset();
  
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
       eHighPerformance_14bit                   = 0x04,/<High-Performance Mode,14-bit resolution>/
       eContLowPwr4_14bit                      = 0x03,/<Continuous measurement,Low-Power Mode 4(14-bit resolution)>/
       eContLowPwr3_14bit                      = 0x02,/<Continuous measurement,Low-Power Mode 3(14-bit resolution)>/
       eContLowPwr2_14bit                      = 0x01,/<Continuous measurement,Low-Power Mode 2(14-bit resolution)/
       eContLowPwr1_12bit                  = 0x00,/<Continuous measurement,Low-Power Mode 1(12-bit resolution)>/
       eSingleLowPwr4_14bit                    = 0x0b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>/
       eSingleLowPwr3_14bit                    = 0x0a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>/
       eSingleLowPwr2_14bit                    = 0x09,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>/
       eSingleLowPwr1_12bit                = 0x08,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>/
       eHighPerformanceLowNoise_14bit           = 0x14,/<High-Performance Mode,Low-noise enabled,14-bit resolution>/
       eContLowPwrLowNoise4_14bit              = 0x13,/<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>/
       eContLowPwrLowNoise3_14bit              = 0x12,/<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>/
       eContLowPwrLowNoise2_14bit              = 0x11,/<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>/
       eContLowPwrLowNoise1_12bit          = 0x10,/<Continuous measurement,Low-Power Mode 1(12-bit resolution,Low-noise enabled)>/
       eSingleLowPwrLowNoise4_14bit            = 0x1b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>/
       eSingleLowPwrLowNoise3_14bit            = 0x1a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>/
       eSingleLowPwrLowNoise2_14bit            = 0x19,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>/
       eSingleLowLowNoisePwr1_12bit        = 0x18,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>/
  */
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise1_12bit);

  /**！
    Set the sensor data collection rate:
               eRate_0hz           /<测量关闭>/
               eRate_1hz6_lp_only  /<1.6hz>/
               eRate_12hz5         /<12.5hz>/
               eRate_25hz          
               eRate_50hz          
               eRate_100hz         
               eRate_200hz         
               eRate_400hz         
               eRate_800hz         
               eRate_1k6hz         
  */
  acce.setDataRate(DFRobot_LIS2DW12::eRate_800hz);
  
  //Enable click detection in the X direction
  acce.enableTapDetectionOnZ(true);
  //Enable click detection in Y direction
  acce.enableTapDetectionOnY(true);
  //Enable click detection in the Z direction
  acce.enableTapDetectionOnX(true);
  //The threshold setting in the X direction 
  //Threshold(mg),Can only be used in the range of ±2g
  acce.setTapThresholdOnX(/*Threshold = */500);
  //The threshold setting in the Y direction   //Threshold(mg),Can only be used in the range of ±2g
  acce.setTapThresholdOnY(/*Threshold = */500);
  //The threshold setting in the Z direction   //Threshold(mg),Can only be used in the range of ±2g)
  acce.setTapThresholdOnZ(/*Threshold = */500);
  
  
  /*
    设置检测双击时，两次点击的间隔时间
    dur duration(0 ~ 3)
    time = dur * (1/ODR)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time(s)      |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
  */
  acce.setTapDur(/*dur=*/3);
  
  /**！
    Set click detection mode:
    eOnlySingle(single click)
    eBothSingleDouble(Single click and double click)
  */
  acce.setTapMode(DFRobot_LIS2DW12::eBothSingleDouble);
  
  /**！
    Set the interrupt source of the int1 pin:
    eDoubleTap(Double click)
    eFreeFall(Free fall)
    eWakeUp(wake)
    eSingleTap(single-Click)
    e6D(Orientation change check)
  */
  acce.setiInt1Event(DFRobot_LIS2DW12::eDoubleTap);

  delay(1000);
}

void loop(void){
  //Click detected
  DFRobot_LIS2DW12:: eTap_t tapEvent = acce.tapDetect();
  //点击方向的源头检测
  DFRobot_LIS2DW12::eTapDir_t dir = acce.getTapDirection();
  uint8_t tap = 0;
  if(tapEvent  == DFRobot_LIS2DW12::eSingleClick){
      Serial.print("single click Detected :");
      tap = 1;
  }
  if(tapEvent  == DFRobot_LIS2DW12::eDoubleClick){  
      Serial.print("Double Tap Detected :");
      tap = 1;
  }
  if(tap == 1){
      if(dir == DFRobot_LIS2DW12::eDirXUp){
        Serial.println("Click it in the positive direction of x");
      }else if(dir == DFRobot_LIS2DW12::eDirXDown){
        Serial.println("Click it in the negative direction of x");
      }else if(dir == DFRobot_LIS2DW12::eDirYUp){
        Serial.println("Click it in the positive direction of y");
      }else if(dir == DFRobot_LIS2DW12::eDirYDown){
        Serial.println("Click it in the negative direction of y");
      }else if(dir == DFRobot_LIS2DW12::eDirZUp){
        Serial.println("Click it in the positive direction of z");
      }else if(dir == DFRobot_LIS2DW12::eDirZDown){
        Serial.println("Click it in the negative direction of z");
      }
      tap = 0;
  }
}