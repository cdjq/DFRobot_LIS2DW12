/**！
 * @file interrupt.ino
 * @brief 中断检测
 * @brief 中断检测
 * @n本示例中使能eZHigherThanTh中断事件，即当Z方向的加速度大于程序所设置的阈值时，在我们
 * @n设置的中断引脚int1/int2上可以检测到中断电平，通过检测中断引脚上的电平变化即可判断是
 * @n否发生该中断事件。可设置的中断事件有以下6个： eXHigherThanTh, eXLowerThanTh, 
 * @n eYHigherThanTh, eYLowerThanTh, eZHigherThanTh,eZLowerThanTh,关于每个中断事件的详细
 * @n解释请看函数enableInterruptEvent()注释
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_LIS
 */
#include <DFRobot_LIS.h>

//当你使用I2C通信时,使用下面这段程序,使用DFRobot_H3LIS200DL_I2C构造对象
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
//DFRobot_H3LIS200DL_I2C acce(&Wire,0x19);
DFRobot_H3LIS200DL_I2C acce;

//当你使用SPI通信时,使用下面这段程序,使用DFRobot_H3LIS200DL_SPI构造对象
#if defined(ESP32) || defined(ESP8266)
#define H3LIS200DL_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define H3LIS200DL_CS 3
#elif (defined NRF5)
#define H3LIS200DL_CS P3
#endif
/*!
 * @brief Constructor 
 * @param cs : Chip selection pinChip selection pin
 * @param spi :SPI controller
 */
//DFRobot_H3LIS200DL_SPI acce(/*cs = */H3LIS200DL_CS);

//中断产生标志
volatile bool intFlag = false;

void interEvent(){
  intFlag = true;
}

void setup(void){

  Serial.begin(9600);
    //Chip initialization
  while(!acce.begin()){
     delay(1000);
     Serial.println("初始化失败，请检查连线与I2C地址设置");
  }
  //Get chip id
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  
  /**
    set range:Range(g)
              eH3lis200dl_100g,/< ±100g>/
              eH3lis200dl_200g,/< ±200g>/
  */
  acce.setRange(/*Range = */DFRobot_LIS::eH3lis200dl_100g);


  /**
    Set data measurement rate：
      ePowerDown_0HZ = 0,
      eLowPower_halfHZ,
      eLowPower_1HZ,
      eLowPower_2HZ,
      eLowPower_5HZ,
      eLowPower_10HZ,
      eNormal_50HZ,
      eNormal_100HZ,
      eNormal_400HZ,
      eNormal_1000HZ,
  */
  acce.setAcquireRate(/*Rate = */DFRobot_LIS::eNormal_50HZ);
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

  /**
    Set the threshold of interrupt source 1 interrupt
    threshold:Threshold(g)
   */
  acce.setInt1Th(/*Threshold = */6);//单位为:g

  /*!
    Enable interrupt
    Interrupt pin selection:
      eINT1 = 0,/<int1 >/
      eINT2,/<int2>/
    Interrupt event selection:
      eXLowerThanTh ,/<The acceleration in the x direction is less than the threshold>/
      eXHigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
      eYLowerThanTh,/<The acceleration in the y direction is less than the threshold>/
      eYHigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
      eZLowerThanTh,/<The acceleration in the z direction is less than the threshold>/
      eZHigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   */
  acce.enableInterruptEvent(/*int pin*/DFRobot_LIS::eINT1,/*interrupt event = */DFRobot_LIS::eZHigherThanTh);
  
  delay(1000);
}

void loop(void){
    //Get the acceleration in the three directions of xyz
    //测量的量程为±100g或±200g,通过setRange()函数设置
    Serial.print("Acceleration x: "); 
    Serial.print(acce.readAccX());
    Serial.print(" g \ty: ");
    Serial.print(acce.readAccY());
    Serial.print(" g \tz: ");
    Serial.print(acce.readAccZ());
    Serial.println(" g");
    delay(300);
   //The interrupt flag is set
   if(intFlag == true){
      //Check wheher the interrupt event is generated in interrupt 1
      if(acce.getInt1Event(DFRobot_LIS::eYHigherThanTh)){
        Serial.println("The acceleration in the y direction is greater than the threshold");
      }
     if(acce.getInt1Event(DFRobot_LIS::eZHigherThanTh)){
       Serial.println("The acceleration in the z direction is greater than the threshold");
      }
      if(acce.getInt1Event(DFRobot_LIS::eXHigherThanTh)){
        Serial.println("The acceleration in the x direction is greater than the threshold");
      }
      intFlag = false;
   }
}
