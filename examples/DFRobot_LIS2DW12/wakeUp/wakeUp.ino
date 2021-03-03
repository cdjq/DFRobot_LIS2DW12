/**！
 * @file wakeUp.ino
 * @brief Wake up the sensor from sleep, and get 
 * @n the movement in which direction wakes up the sensor
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
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS);

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
    eHighPerformance           
    eContLowPwr_4              
    eContLowPwr_3              
    eContLowPwr_2              
    eContLowPwr_12bit          
    eSingleLowPwr_4            
    eSingleLowPwr_3            
    eSingleLowPwr_2            
    eSingleLowPwr_12bit        
    eHighPerformanceLowNoise   
    eContLowPwrLowNoise_4      
    eContLowPwrLowNoise_3      
    eContLowPwrLowNoise_2      
    eContLowPwrLowNoise_12bit  
    eSingleLowPwrLowNoise_4    
    eSingleLowPwrLowNoise_3    
    eSingleLowPwrLowNoise_2    
    eSingleLowLowNoisePwr_12bit
  */
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise_12bit);
  
  /**！
    Set the sensor data collection rate:
    
    eOdr_off         
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
  acce.setDataRate(DFRobot_LIS2DW12::eOdr_200hz);
  
  /**！
    Filter settings:
    eLpfOnOut(Low pass filter)
    eUserOffsetOnOut(User set data offset)
    eHighPassOnOut(High pass filter)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLpfOnOut);
  
  /**!
     Set the wake-up duration
     1 LSB = 1 * 1/ODR (measurement frequency)
     range：0~3
   */
  acce.setWakeupDur(2);
  //Set wakeup threshold,unit:g
  //数值是在量程之内
  acce.setWakeupThreshold(0.5);
  
  
  /**！
    Set the interrupt source of the int1 pin:
    eDoubleTap(Double click)
    eFfEvent(Free fall)
    eWakeupEvent(wake)
    eSingleTap(single-Click)
    eTnt16d(Orientation change check)
  */
  acce.setPinInt1Route(DFRobot_LIS2DW12::eWakeupEvent);
  
  delay(1000);
}

void loop(void){

   //Wake-up event detected
   if(acce.actDetect()){
     Serial.println("Wake-Up event on");
     DFRobot_LIS2DW12::eWakeupDir_t dir  = acce.getWakeupDir();
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