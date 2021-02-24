/**！
 * @file getAcceleration.ino
 * @brief Get the acceleration in x, y, z directions,范围(±2g/±4g/±8g/±16g)
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
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS);

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
  //Set whether to collect data continuously
  acce.continRefresh(true);
  
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
  acce.setDataRate(DFRobot_LIS2DW12::eOdr_50hz);
  
  /**！
    Set the sensor measurement range:
                   e2_g   /<±2g>/
                   e4_g   /<±4g>/
                   e8_g   /<±8g>/
                   e16_g  /< ±16g>/
  */
  acce.setRange(DFRobot_LIS2DW12::e2_g);
  
  
  /**！
    Filter settings:
    eLpfOnOut(Low pass filter)
    eHighPassOnOut(High pass filter)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLpfOnOut);
  
  /**！
    Set bandwidth：
        eOdrDiv_2     = 0,/<ODR/2 (up to ODR = 800 Hz, 400 Hz when ODR = 1600 Hz)>/
        eOdrDiv_4     = 1,/<ODR/4 (High Power/Low power)>*
        eOdrDiv_10    = 2,/<ODR/10 (HP/LP)>/
        eOdrDiv_20    = 3,/< ODR/20 (HP/LP)>/
  */
  acce.setFilterBandwidth(DFRobot_LIS2DW12::eOdrDiv_4);
  
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
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise_2);
  
  delay(1000);
}

void loop(void){
   
    Serial.print("Acceleration x: ");
    //Read the acceleration in the x direction
    Serial.print(acce.readAccX());
    Serial.print(" mg \t  y:");
    //Read the acceleration in the y direction
    Serial.print(acce.readAccY());
    Serial.print(" mg \t  z:");
    //Read the acceleration in the z direction
    Serial.print(acce.readAccZ());
    Serial.println(" mg");
    delay(300);
}