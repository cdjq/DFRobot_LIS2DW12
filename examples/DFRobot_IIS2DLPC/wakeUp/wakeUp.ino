/**！
 * @file wakeUp.ino
 * @brief 当x,y,z中某个方向的加速度大于设置好的阈值时,芯片会产生wake-up事件，通过
 * @n 访问芯片寄存器可以知道是从哪一个方向的运动唤醒了芯片
 * @n 本示例中需要使用setWakeUpThreshold()设置唤醒持续时间,当芯片被唤醒后,芯片会持续一段时间才进入睡眠状态
 * @n 还会使用setWakeUpDur()设置threshold,当加速度的变化大于此值时,会触发eWakeUp事件
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
//FRobot_IIS2DLPC_I2C acce(&Wire,0x19);
DFRobot_IIS2DLPC_I2C acce;

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
 * @param cs  Chip selection pinChip selection pin
 * @param spi SPI controller
 */
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS,&SPI);
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS);

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
  acce.setDataRate(DFRobot_LIS2DW12::eRate_200hz);
  
  /**！
    Filter settings:
           eLPF(Low pass filter)
           eHPF(High pass filter)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);
  
  /**
    唤醒持续时间,当芯片被唤醒后,芯片会持续一段时间才进入睡眠状态
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
  acce.setWakeUpDur(/*dur =*/2);
  
  //Set wakeup threshold,当加速度的变化大于此值时,会触发eWakeUp事件,unit:mg
  //数值是在量程之内
  acce.setWakeUpThreshold(/*threshold = */0.5);
  
  /**！
    Set the interrupt event of the int1 pin:
    eDoubleTap(Double click)
    eFreeFall(Free fall)
    eWakeUp(wake)
    eSingleTap(single-Click)
    e6D(Orientation change check)
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eWakeUp);
  
  /**！
    Set the interrupt event of the int1 pin:
       eSleepChange = 0x40,/<Sleep change status routed to INT2 pad>/
       eSleepState  = 0x80,/<Enable routing of SLEEP_STATE on INT2 pad>/
  */
  //acce.setInt2Event(DFRobot_LIS2DW12::eSleepChange);
  delay(100);
}

void loop(void){

   //Wake-up event detected
   if(acce.actDetected()){
     Serial.println("Wake-Up event on");
     //唤醒的运动方向检测
     DFRobot_LIS2DW12::eWakeUpDir_t dir  = acce.getWakeUpDir();
     if(dir == DFRobot_LIS2DW12::eDirX){
       Serial.println("x  direction");
     }
     if(dir == DFRobot_LIS2DW12::eDirY){
       Serial.println("y direction");
     }
     if(dir == DFRobot_LIS2DW12::eDirZ){
       Serial.println("z direction");
     }
     delay(100);
   }
}