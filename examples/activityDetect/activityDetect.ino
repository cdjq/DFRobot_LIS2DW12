/**！
 * @file activityDetect.ino
 * @brief Motion detection
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_DFRobot_IIS2DLPC
 */


#include <DFRobot_IIS2DLPC.h>
#if defined(ESP32) || defined(ESP8266)
#define IIS2DLPC_CS  D5

/* AVR series mainboard */
#else
#define IIS2DLPC_CS 2
#endif
/*!
 * @brief Constructor 
 * @param cs : Chip selection pinChip selection pin
 * @param spi :SPI controller
 */
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS);
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x64/0x65/0x660x67)
 */
DFRobot_IIS2DLPC_I2C acce;
void setup(void){

  Serial.begin(9600);
  while(acce.begin()){
     delay(1000);
     Serial.println("init failure");
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  //Software reset
  acce.softReset();
  
  /**！
    Set the sensor measurement range:
    eIIS2DLPC_2g     
    eIIS2DLPC_4g     
    eIIS2DLPC_8g     
    eIIS2DLPC_16g 
  */
  acce.setRange(DFRobot_IIS2DLPC::eIIS2DLPC_2g);
  
  /**！
    Filter settings:
    eIIS2DLPC_LPF_ON_OUT(Low pass filter)
    eIIS2DLPC_USER_OFFSET_ON_OUT(User set data offset)
    eIIS2DLPC_HIGH_PASS_ON_OUT(High pass filter)
  */
  acce.setFilterPath(DFRobot_IIS2DLPC::eIIS2DLPC_LPF_ON_OUT);
  
  /**！
    Set bandwidth：
    eIIS2DLPC_ODR_DIV_2     = 0,
    eIIS2DLPC_ODR_DIV_4     = 1,
    eIIS2DLPC_ODR_DIV_10    = 2,
    eIIS2DLPC_ODR_DIV_20    = 3,
  */
  acce.setFilterBandwidth(DFRobot_IIS2DLPC::eIIS2DLPC_ODR_DIV_4);
  
  //Interrupt setting, open when using interrupt
  //attachInterrupt(0,interEvent, CHANGE);
  
  //Set wake-up duration (0~3), four levels
  acce.setWakeupDur(2);
  //Set wakeup threshold，1 LSB = 1/64 of g(0~31)
  acce.setWakeupThreshold(10);

  //Set the duration of the sleep state (you need to enter the sleep state for a certain period of time before it can be detected again) 1 LSB = 512 * 1/ODR (data acquisition frequency)
  acce.setActSleepDur(2);
  
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
  acce.setPowerMode(DFRobot_IIS2DLPC::eContLowPwrLowNoise_12bit);
  
  /**！
    Set the mode of motion detection:
    eNoDetection     
    eDetectActInact  
    eDetectStatMotion
  */
  acce.setActMode(DFRobot_IIS2DLPC::eDetectActInact);
  
  /**！
    Set the interrupt source of the int1 pin:
    eDoubleTap(Double click)
    eFfEvent(Free fall)
    eWakeupEvent(wake)
    eSingleTap(single-Click)
    eTnt16d(Orientation change check)
  */
  acce.setPinInt1Route(DFRobot_IIS2DLPC::eWakeupEvent);
  
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
  acce.setDataRate(DFRobot_IIS2DLPC::eOdr_200hz);
  delay(1000);
}

void loop(void){
   DFRobot_IIS2DLPC::sAllSources_t source= acce.getAllSources();
   //Motion detected
   if(source.wakeUp.wuIa){
     Serial.println("Activity Detected");
   }
   if(source.wakeUp.sleepStateIa){
     Serial.println("Inactivity Detected");
   }

  delay(300);
}