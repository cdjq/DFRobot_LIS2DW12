/**！
 * @file tap.ino
 * @brief Single tap and double tap detection,点击模块，或者点击模块附件的桌面都可以触发点击事件
 * @n 可以通过setTapMode()函数选择只检测单击，或单击和双击同时检测
 * @n 在使用SPI时片选引脚可以通过 LIS2DW12_CS 的值修改
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
//DFRobot_LIS2DW12_I2C acce(&Wire,0x19);
DFRobot_LIS2DW12_I2C acce;


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
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS,&SPI);
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS);

void setup(void){
  Serial.begin(9600);
  while(!acce.begin()){
     Serial.println("通信失败，请检查连线是否准确,使用I2C通信时检查地址是否设置准确");
     delay(1000);
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
       eHighPerformance_14bit         /<High-Performance Mode,14-bit resolution>/
       eContLowPwr4_14bit             /<Continuous measurement,Low-Power Mode 4(14-bit resolution)>/
       eContLowPwr3_14bit             /<Continuous measurement,Low-Power Mode 3(14-bit resolution)>/
       eContLowPwr2_14bit             /<Continuous measurement,Low-Power Mode 2(14-bit resolution)/
       eContLowPwr1_12bit             /<Continuous measurement,Low-Power Mode 1(12-bit resolution)>/
       eSingleLowPwr4_14bit           /<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>/
       eSingleLowPwr3_14bit           /<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>/
       eSingleLowPwr2_14bit           /<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>/
       eSingleLowPwr1_12bit           /<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>/
       eHighPerformanceLowNoise_14bit /<High-Performance Mode,Low-noise enabled,14-bit resolution>/
       eContLowPwrLowNoise4_14bit     /<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>/
       eContLowPwrLowNoise3_14bit     /<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>/
       eContLowPwrLowNoise2_14bit     /<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>/
       eContLowPwrLowNoise1_12bit     /<Continuous measurement,Low-Power Mode 1(12-bit resolution,Low-noise enabled)>/
       eSingleLowPwrLowNoise4_14bit   /<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>/
       eSingleLowPwrLowNoise3_14bit   /<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>/
       eSingleLowPwrLowNoise2_14bit   /<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>/
       eSingleLowPwrLowNoise1_12bit   /<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>/
  */
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise1_12bit);

  /**！
    Set the sensor data collection rate:
               eRate_0hz           /<测量关闭>/
               eRate_1hz6          /<1.6hz,仅在低功耗模式下使用>/
               eRate_12hz5         /<12.5hz>/
               eRate_25hz          
               eRate_50hz          
               eRate_100hz         
               eRate_200hz         
               eRate_400hz       /<仅在High-Performance mode下使用>/
               eRate_800hz       /<仅在High-Performance mode下使用>/
               eRate_1k6hz       /<仅在High-Performance mode下使用>/
               eSetSwTrig        /<软件触发单次测量>/
  */
  acce.setDataRate(DFRobot_LIS2DW12::eRate_800hz);
  
  //Enable tap detection in the X direction
  acce.enableTapDetectionOnZ(true);
  //Enable tap detection in Y direction
  acce.enableTapDetectionOnY(true);
  //Enable tap detection in the Z direction
  acce.enableTapDetectionOnX(true);
  //The threshold setting in the X direction 
  //Threshold(mg),Can only be used in the range of ±2g
  acce.setTapThresholdOnX(/*Threshold = */0.5);
  //The threshold setting in the Y direction   //Threshold(mg),Can only be used in the range of ±2g
  acce.setTapThresholdOnY(/*Threshold = */0.5);
  //The threshold setting in the Z direction   //Threshold(mg),Can only be used in the range of ±2g)
  acce.setTapThresholdOnZ(/*Threshold = */0.5);
  
  
  /*
    设置检测双击时，两次点击的间隔时间
    dur duration(0 ~ 15)
    time = dur * (1/ODR)(unit:s)
    |                                  参数与时间之间的线性关系的示例                                                          |
    |------------------------------------------------------------------------------------------------------------------------|
    |                |                     |                          |                          |                           |
    |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
    |------------------------------------------------------------------------------------------------------------------------|
    |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
    |------------------------------------------------------------------------------------------------------------------------|
  */
  acce.setTapDur(/*dur=*/3);
  
  /**！
    Set tap detection mode:
       eOnlySingle(single tap)
       eBothSingleDouble(Single tap and double tap)
  */
  acce.setTapMode(DFRobot_LIS2DW12::eBothSingleDouble);
  
  /**！
    Set the interrupt source of the int1 pin:
      eDoubleTap(Double tap)
      eFreeFall(Free fall)
      eWakeUp(wake)
      eSingleTap(single-tap)
      e6D(Orientation change check)
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eDoubleTap);

  delay(1000);
}

void loop(void){
  //tap detected
  DFRobot_LIS2DW12:: eTap_t tapEvent = acce.tapDetect();
  //点击的源头检测
  DFRobot_LIS2DW12::eTapDir_t dir = acce.getTapDirection();
  uint8_t tap = 0;
  if(tapEvent  == DFRobot_LIS2DW12::eSTap){
      Serial.print("single tap Detected :");
      tap = 1;
  }
  if(tapEvent  == DFRobot_LIS2DW12::eDTap){  
      Serial.print("Double Tap Detected :");
      tap = 1;
  }
  if(tap == 1){
      if(dir == DFRobot_LIS2DW12::eDirXUp){
        Serial.println("tap it in the positive direction of x");
      }else if(dir == DFRobot_LIS2DW12::eDirXDown){
        Serial.println("tap it in the negative direction of x");
      }else if(dir == DFRobot_LIS2DW12::eDirYUp){
        Serial.println("tap it in the positive direction of y");
      }else if(dir == DFRobot_LIS2DW12::eDirYDown){
        Serial.println("tap it in the negative direction of y");
      }else if(dir == DFRobot_LIS2DW12::eDirZUp){
        Serial.println("tap it in the positive direction of z");
      }else if(dir == DFRobot_LIS2DW12::eDirZDown){
        Serial.println("tap it in the negative direction of z");
      }
      tap = 0;
  }
}