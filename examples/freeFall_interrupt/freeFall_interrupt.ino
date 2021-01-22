/**！
 * @file freeFall_interrupt.ino
 * @brief Interrupt detection of free fall
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

volatile int Flag = 0;
void interEvent(){
  Flag = 1;
  Serial.println("----------------------interrupt Detected------------------------");
}

void setup(void){

  Serial.begin(9600);
  while(acce.begin()){
     delay(1000);
     Serial.println("init failure");
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  
  //Interrupt setting, open when using interrupt
  attachInterrupt(0,interEvent, CHANGE);
  
  //Chip soft reset
  acce.softReset();
  //Set whether to collect data continuously
  acce.continRefresh(true);
  
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
  acce.setPowerMode(DFRobot_IIS2DLPC::eContLowPwr_4);
  
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
  acce.setDataRate(DFRobot_IIS2DLPC::eOdr_100hz);
  
  /**！
    Set the sensor measurement range:
    eIIS2DLPC_2g     
    eIIS2DLPC_4g     
    eIIS2DLPC_8g     
    eIIS2DLPC_16g 
  */
  acce.setRange(DFRobot_IIS2DLPC::eIIS2DLPC_2g);
  
  //The duration of free fall (0~31), the larger the value, the longer the free fall time is needed to be detected
  //1 LSB = 1 * 1/ODR (measurement frequency)
  acce.setFrDur(0x06);
  
  /**！
    Set the interrupt source of the int1 pin:
    eDoubleTap(Double click)
    eFfEvent(Free fall)
    eWakeupEvent(wake)
    eSingleTap(single-Click)
    eTnt16d(Orientation change check)
  */
  acce.setPinInt1Route(DFRobot_IIS2DLPC::eFfEvent);
  //Latch interrupt
  acce.latchInterrupt(true);
  delay(1000);
}

void loop(void){
   if(Flag == 1){
   //Get the status of all events
   DFRobot_IIS2DLPC::sAllSources_t source= acce.getAllSources();
   //Free fall event is detected
   if(source.wakeUp.ffIa){

    Serial.println("free fall detected\r\n");
    delay(300);
   }
    Flag = 0;
   }

}