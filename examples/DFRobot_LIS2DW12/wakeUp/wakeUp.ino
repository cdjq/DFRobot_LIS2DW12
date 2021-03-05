/**！
 * @file wakeUp.ino
 * @brief 当x,y,z中某个方向的加速度大于设置好的阈值时,芯片会产生wake-up事件，通过
 * @访问芯片可以知道是从哪一个方向的运动唤醒了芯片
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
DFRobot_LIS2DW12_I2C acce/*(&Wire,0x19)*/;

//当你使用SPI通信时,使用下面这段程序,使用DFRobot_LIS2DW12_SPI构造对象
#if defined(ESP32) || defined(ESP8266)
#define LIS2DW12_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define LIS2DW12_CS  3
#elif (defined NRF5)
#define LIS2DW12_CS  P3
#endif
/*!
 * @brief Constructor 
 * @param cs : Chip selection pinChip selection pin
 * @param spi :SPI controller
 */
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS,&SPI);
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS);
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
  acce.setDataRate(DFRobot_LIS2DW12::eRate_200hz);
  
  /**！
    Filter settings:
           eLPF(Low pass filter)
           eHPF(High pass filter)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);
  
  /**
   唤醒持续时间
    dur (0 ~ 31)
    time = dur * (1/Rate)(unit:s)
   */
  acce.setWakeUpDur(/*dur =*/2);
  //Set wakeup threshold,unit:mg
  //数值是在量程之内
  acce.setWakeUpThreshold(/*threshold = */0.5);
  
  /**！
    Set the interrupt source of the int1 pin:
    eDoubleTap(Double click)
    eFreeFall(Free fall)
    eWakeUp(wake)
    eSingleTap(single-Click)
    e6D(Orientation change check)
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eWakeUp);
  
  delay(100);
}

void loop(void){

   //Wake-up event detected
   if(acce.actDetect()){
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