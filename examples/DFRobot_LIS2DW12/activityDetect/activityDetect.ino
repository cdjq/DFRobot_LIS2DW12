/**！
 * @file activityDetect.ino
 * @brief Motion detection,可以检测到模块是否在移动
 * @n 使用此功能,需先进入低功耗模式,然后调用setActMode(),使芯片进入睡眠模式,此种状态下测量速率为12.5hz
 * @n 当检测到某个方向的加速度变化大于阈值时测量速率会提升到设置的正常速率，阈值大小通过setWakeUpThreshold()函数设置
 * @n 但如果停止运动即三个方向加速度的变化小于阈值芯片会在一段时间后进入进入睡模式,这个持续的时间由setWakeUpDur()函数设置
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
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS);
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS,&SPI);

void setup(void){
  Serial.begin(9600);
  while(!acce.begin()){
     Serial.println("通信失败，请检查连线是否准确,使用I2C通信时检查地址是否设置准确");
     delay(1000);
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  //Software reset
  acce.softReset();
  
  /**！
    Set the sensor measurement range:
                   e2_g   /<±2g>/
                   e4_g   /<±4g>/
                   e8_g   /<±8g>/
                   e16_g  /<±16g>/
  */
  acce.setRange(DFRobot_LIS2DW12::e2_g);
  
  /**！
    Filter settings:
           eLPF(Low pass filter)
           eHPF(High pass filter)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);
  
  /**！
    Set bandwidth：
        eRateDiv_2  ,/<Rate/2 (up to Rate = 800 Hz, 400 Hz when Rate = 1600 Hz)>/
        eRateDiv_4  ,/<Rate/4 (High Power/Low power)>*
        eRateDiv_10 ,/<Rate/10 (HP/LP)>/
        eRateDiv_20 ,/< Rate/20 (HP/LP)>/
  */
  acce.setFilterBandwidth(DFRobot_LIS2DW12::eRateDiv_4);
  
  /**
      唤醒持续时间,在setActMode()函数使用eDetectAct的检测模式时,芯片在被唤醒后,会持续一段时
    间以正常速率采集数据,然后便会继续休眠,以12.5hz的频率采集数据
    dur (0 ~ 3)
    time = dur * (1/Rate)(unit:s)
    |                                  参数与时间之间的线性关系的示例                                                          |
    |------------------------------------------------------------------------------------------------------------------------|
    |                |                     |                          |                          |                           |
    |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
    |------------------------------------------------------------------------------------------------------------------------|
    |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
    |------------------------------------------------------------------------------------------------------------------------|
   */
  acce.setWakeUpDur(/*dur = */2);
  
  //Set wakeup threshold,当加速度的变化大于此值时,会触发eWakeUp事件,unit:mg
  //数值是在量程之内
  acce.setWakeUpThreshold(/*threshold = */0.2);
  
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
    Set the mode of motion detection:
    eNoDetection       /<No detection>/
    eDetectAct         /<设置此模式,芯片的速率会降为12.5hz,并且在eWakeUp事件产生后,变为正常测量频率>/
    eDetectStatMotion  /<此模式,仅能检测芯片是否处于睡眠模式,而不改变测量频率和电源模式,一直以正常测量频率测量数据>/
  */
  acce.setActMode(DFRobot_LIS2DW12::eDetectAct);
  
  /**！
    Set the interrupt source of the int1 pin:
    eDoubleTap(Double click)
    eFreeFall(Free fall)
    eWakeUp(wake up)
    eSingleTap(single-Click)
    e6D(Orientation change check)
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eWakeUp);
  
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
  acce.setDataRate(DFRobot_LIS2DW12::eRate_200hz);
  delay(100);
}

void loop(void){
   //Motion detected
   if(acce.actDetected()){
     Serial.println("Activity Detected");
     delay(100);
   }
  
}